// sdl tetris game

// stdlib includes
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

// third party includes
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> //enables the loading of png files
#include <SDL2/SDL_mixer.h> //enables the use of audio
#include <SDL2/SDL_ttf.h>   //enables text output to renderer

// local includes
#include "GameRenderer.hpp"

// window constants
#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 448
#define GRID_SIZE 32

// function prototypes
SDL_Window *initializeGame(SDL_Window *);
int readInputs();
int updateGame(int, int);
void gameRenderer(int);

struct tetromino {
    int x;
    int y;
    int theta;
    SDL_Rect r1;
    SDL_Rect r2;
    SDL_Rect r3;
    SDL_Rect r4;
    //virtual void rotate() = 0;
};

struct iTetromino : tetromino
{

    iTetromino(int x_val, int y_val, int theta_val) {
    SDL_Rect r1 = {x, y, GRID_SIZE, GRID_SIZE};
    SDL_Rect r2 = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
    SDL_Rect r3 = {x + 64, y, GRID_SIZE, GRID_SIZE};
    SDL_Rect r4 = {x + 96, y, GRID_SIZE, GRID_SIZE};
    }
    /*
    void rotate() {
        theta = (theta + 90) % 360;
        switch (theta) {
            case 0:
            r1 = {x, y, GRID_SIZE, GRID_SIZE};
            r2 = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};;
            r3 = {x + 64, y, GRID_SIZE, GRID_SIZE};
            r4 = {x + 96, y, GRID_SIZE, GRID_SIZE};
            break;
            default;
        }
    }
    */
};

struct jTetromino : tetromino
{
    int x;
    int y;
    SDL_Rect r1 = {x,y};
    SDL_Rect r2 = {};
    SDL_Rect r3 = {};
    SDL_Rect r4 = {};
};
struct lTetromino : tetromino
{
    int x;
    int y;
    SDL_Rect r1;
    SDL_Rect r2;
    SDL_Rect r3;
    SDL_Rect r4;
};
struct oTetromino : tetromino
{
    int x;
    int y;
    SDL_Rect r1;
    SDL_Rect r2;
    SDL_Rect r3;
    SDL_Rect r4;
};
struct sTetromino : tetromino
{
    int x;
    int y;
    SDL_Rect r1;
    SDL_Rect r2;
    SDL_Rect r3;
    SDL_Rect r4;
};
struct zTetromino : tetromino
{
    int x;
    int y;
    SDL_Rect r1;
    SDL_Rect r2;
    SDL_Rect r3;
    SDL_Rect r4;
};



int main(int argc, char *argv[])
{

    /*
        // initialize SDL, SDL_image, SDL_ttf, and SDL_mixer
        SDL_Window* window = nullptr;
        window = initializeGame(window);
    */
    // initialize render window
    GameRenderer gWindow("GAME v0.1", SCREEN_WIDTH, SCREEN_HEIGHT);

    // game variables
    bool isRunning = true;
    int gameInputs = 0;
    int gameState = 0;
    int x_tet = 64;
    int y_tet = 64;
    int theta = 0;
    iTetromino it = iTetromino(x_tet,y_tet,theta);

    // main game loop
    while (isRunning)
    {

        // SET background color
        int background[4] = {255, 255, 255, 255};
        gWindow.changeColor(background);
        gWindow.clear();

        // draw grid (10x40)
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
        it = {x_tet, y_tet, theta};
        SDL_Rect tetromino[4] = {it.r1, it.r2, it.r3, it.r4};
        gWindow.renderRects(tetromino);

        //display screen
        gWindow.display();

        // read inputs
        // gameInputs = readInputs();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameInputs = 1;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    y_tet -= GRID_SIZE;
                    break;

                case SDLK_DOWN:
                    y_tet += GRID_SIZE;    
                    break;

                case SDLK_LEFT:
                    x_tet -= GRID_SIZE;
                    break;

                case SDLK_RIGHT:
                    x_tet += GRID_SIZE;
                    break;

                default:
                    break;
                }
            }
        }

        // update game
        // gameState = updateGame(gameInputs, gameState);
        // make the block drop
        y_tet += GRID_SIZE;
        y_tet = std::max(y_tet, 64);
        y_tet = std::min(y_tet, 672);
        x_tet = std::max(x_tet, 64);
        x_tet = std::min(x_tet, 256);
        if (gameInputs == 1)
        {
            isRunning = false;
        }

        SDL_Delay(500);
    }

    std::cout << "Shutting Down" << std::endl;
    SDL_Delay(2000);
    gWindow.destroy();
    SDL_Quit();

    return 0;
}

SDL_Window *initializeGame(SDL_Window *window)
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        printf("SDL failed to init! SDL Error: %s\n", SDL_GetError());
    }

    /*
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
            printf("IMG failed to init! IMG Error: %s\n", IMG_GetError());
    }
    if (TTF_Init() == -1)
    {
            printf("TTF failed to init! TTF Error: %s\n", TTF_GetError());
    }
    */

    window = SDL_CreateWindow("Tetris", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    return window;
}

int readInputs()
{

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return 1;
        }
    }
    return 0;
}
/*
int updateGame(int inputs, int state) {
    if (inputs == 1) {
        state = 1;
    } else {
        state = 0;
    }

    return state;
}
*/
/*
GameRenderer gameRenderer(int state) {
    //render game window here
    // initialize render window
}*/