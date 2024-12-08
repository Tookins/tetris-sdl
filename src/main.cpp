// sdl tetris game

// stdlib includes
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <random>

// third party includes
#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h> //enables the loading of png files
// #include <SDL2/SDL_mixer.h> //enables the use of audio
// #include <SDL2/SDL_ttf.h>   //enables text output to renderer

// local includes
#include "GameRenderer.hpp"
#include "Tetromino.hpp"
#include "GameBoard.hpp"

// window constants
#define SCREEN_HEIGHT 960
#define SCREEN_WIDTH 960
#define GRID_SIZE 32
#define TILE_OFFSET_X 160
#define TILE_OFFSET_Y 64
#define FPS 60
#define DIFF_SCALE 1.0
// function prototypes
Tetromino *getRandomTet(int num);

int main(int argc, char *argv[])
{

    // initialize render window
    GameRenderer gWindow("GAME v0.1", SCREEN_WIDTH, SCREEN_HEIGHT);

    // initial game board
    GameBoard gBoard = GameBoard();

    // game variables
    bool isRunning = true;
    int level = 1;
    int gameScore = 0;
    int rowsCleared = 0;
    int rowsToNextLevel = 10;

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // create distribution to randomly generate tiles
    std::uniform_int_distribution<int> tetDist(0, 6);

    // generate the initial tetromino
    int randomNumber = tetDist(gen);
    Tetromino *nextTet = getRandomTet(randomNumber);

    // main game loop
    while (isRunning)
    {
        Tetromino *currTet = nextTet;

        // generate the next random tetromino
        delete nextTet;
        randomNumber = tetDist(gen);
        Tetromino *nextTet = getRandomTet(randomNumber);
        nextTet->setX(704);
        nextTet->setY(288);


        while (!currTet->isStuck())
        {
            // set block color
            int *blockColor = currTet->getColor();

            // frame start
            int framesBetweenMoves = 0;
            while (framesBetweenMoves < DIFF_SCALE * FPS)
            {
                // get ticks at start of frame
                Uint32 initialTicks = SDL_GetTicks();

                // SET background color and foreground color
                int background[4] = {255, 255, 255, 255};
                gWindow.changeColor(background);
                gWindow.clear();

                //draw preview
                int rgbBlack[4] = {0, 0, 0, 255};
                SDL_Rect previewRect = {480, 64, 448, 448};
                gWindow.changeColor(rgbBlack);
                gWindow.renderRect(&previewRect);
                gWindow.changeColor(nextTet->getColor());
                gWindow.renderRects(nextTet->getBlocks());

                //draw scoreboard

                // draw game board
                for (int i = 0; i < gBoard.getHeight(); i++)
                {
                    for (int j = 0; j < gBoard.getWidth(); j++)
                    {
                        Node square = gBoard.getSquare(i, j);
                        gWindow.changeColor(square.m_rgba);
                        gWindow.renderFillRect(&square.m_square);
                    }
                }

                // draw currTetromino
                gWindow.changeColor(currTet->getColor());
                gWindow.renderRects(currTet->getBlocks());

                // draw grid lines
                gWindow.changeColor(rgbBlack);
                for (int j = 0; j <= 10; j++)
                {
                    int vline[4] = {64 + j * GRID_SIZE, 64, 64 + j * GRID_SIZE, 704};
                    gWindow.renderLine(vline);
                }
                for (int i = 0; i <= 20; i++)
                {
                    int hline[4] = {64, 64 + i * GRID_SIZE, 384, 64 + i * GRID_SIZE};
                    gWindow.renderLine(hline);
                }

                // display screen
                gWindow.display();

                bool isTetrominostuck = true; // flag to check if tetromino can move

                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        isRunning = false;
                    }
                    else if (event.type == SDL_KEYDOWN)
                    {

                        switch (event.key.keysym.sym)
                        {

                        case SDLK_UP:
                            currTet->rotate(gBoard);
                            break;

                        case SDLK_DOWN:
                            currTet->moveDown(gBoard);
                            break;

                        case SDLK_LEFT:
                            currTet->moveLeft(gBoard);
                            break;

                        case SDLK_RIGHT:
                            currTet->moveRight(gBoard);
                            break;

                        default:
                            break;
                        }
                    }
                }

                // update game
                Uint32 finalTicks = SDL_GetTicks();
                Uint32 ticksPerFrame = 1000 / FPS;
                SDL_Delay(ticksPerFrame - (finalTicks - initialTicks));
                // end frame
                framesBetweenMoves++;
            }

            // make the block drop
            currTet->moveDown(gBoard);

            // add tetromino to board if it is stuck
            if (currTet->isStuck())
            {
                SDL_Rect *blocks = currTet->getBlocks();
                for (int i = 0; i < 4; i++)
                {
                    int boardX = (blocks[i].x - 32) / 32;
                    int boardY = (blocks[i].y - 64) / 32;
                    gBoard.setSquareColor(boardY, boardX, blockColor);
                    gBoard.closeSquare(boardY, boardX);
                }
            }

            // check if any rows are full top to bottom
            for (int i = 0; i < HEIGHT - 1; i++)
            {
                bool rowFull = true;
                for (int j = 1; j < (WIDTH - 1); j++)
                {
                    if (gBoard.m_squares[i][j].m_open)
                    {
                        rowFull = false;
                        break;
                    }
                }
                if (rowFull) // a completed row exists
                {
                    gBoard.clearRow(i);
                    rowsCleared++;
                    rowsToNextLevel--;
                    if (rowsToNextLevel == 0)
                    {
                        level++;
                        rowsToNextLevel = 10;
                    }
                    gameScore += 80 + 20 * level;
                    std::cout << "score: " << gameScore << std::endl;
                }
            }
        }
        delete currTet;
    }

    std::cout << "Shutting Down" << std::endl;
    gWindow.destroy();
    SDL_Quit();

    return 0;
}

Tetromino *getRandomTet(int randomNumber)
{
    switch (randomNumber)
    {
    case 0:
    {
        ITetromino *tet = new ITetromino(TILE_OFFSET_X, TILE_OFFSET_Y, 0);
        return tet;
        break;
    }
    case 1:
    {
        JTetromino *tet = new JTetromino(TILE_OFFSET_X, TILE_OFFSET_Y, 0);
        return tet;
        break;
    }
    case 2:
    {
        LTetromino *tet = new LTetromino(TILE_OFFSET_X, TILE_OFFSET_Y, 0);
        return tet;
        break;
    }
    case 3:
    {
        OTetromino *tet = new OTetromino(TILE_OFFSET_X, TILE_OFFSET_Y, 0);
        return tet;
        break;
    }
    case 4:
    {
        STetromino *tet = new STetromino(TILE_OFFSET_X, TILE_OFFSET_Y, 0);
        return tet;
        break;
    }
    case 5:
    {
        TTetromino *tet = new TTetromino(TILE_OFFSET_X, TILE_OFFSET_Y, 0);
        return tet;
        break;
    }
    case 6:
    {
        ZTetromino *tet = new ZTetromino(TILE_OFFSET_X, TILE_OFFSET_Y, 0);
        return tet;
        break;
    }
    default:
    {
        ITetromino *tet = new ITetromino(TILE_OFFSET_X, TILE_OFFSET_Y, 0);
        return tet;
        break;
    }
    }
}