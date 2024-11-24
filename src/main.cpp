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
#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 448
#define GRID_SIZE 32
#define TILE_OFFSET_X 160
#define TILE_OFFSET_Y 64

// function prototypes
Tetromino *getRandomTet(int num);

int main(int argc, char *argv[])
{

    // initialize render window
    GameRenderer gWindow("GAME v0.1", SCREEN_WIDTH, SCREEN_HEIGHT);

    // game variables
    bool isRunning = true;

    // initial game board
    GameBoard gBoard = GameBoard();

    // initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // create distribution to randomly generate tiles
    std::uniform_int_distribution<int> tetDist(0, 6);

    // main game loop
    while (isRunning)
    {

        // generate a random tile
        int randomNumber = tetDist(gen);
        Tetromino *tet = getRandomTet(randomNumber);

        while (!tet->isStuck())
        {

            // SET background color
            int background[4] = {255, 255, 255, 255};
            gWindow.changeColor(background);
            gWindow.clear();

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

            // draw grid lines
            int rgb[4] = {0, 0, 0, 255};
            gWindow.changeColor(rgb);
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

            // draw tetromino
            int blockColor[4] = {0, 0, 255, 255};
            gWindow.changeColor(blockColor);
            gWindow.renderRects(tet->getBlocks());

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
                        tet->rotate();
                        break;

                    case SDLK_DOWN:
                        tet->moveDown(gBoard);
                        break;

                    case SDLK_LEFT:
                        tet->moveLeft(gBoard);
                        break;

                    case SDLK_RIGHT:
                        tet->moveRight(gBoard);
                        break;

                    default:
                        break;
                    }
                }
            }

            // update game

            // make the block drop
            tet->moveDown(gBoard);

            // add tetromino to board if it is stuck
            if (tet->isStuck())
            {
                SDL_Rect *blocks = tet->getBlocks();
                for (int i = 0; i < 4; i++)
                {
                    int boardX = (blocks[i].x - 32) / 32;
                    int boardY = (blocks[i].y - 64) / 32;
                    gBoard.setSquareColor(boardY, boardX, blockColor);
                    gBoard.closeSquare(boardY, boardX);
                }
            }

            SDL_Delay(500);
        }
        delete tet;
    }

    std::cout << "Shutting Down" << std::endl;
    SDL_Delay(2000);
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