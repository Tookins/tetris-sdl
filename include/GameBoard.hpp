#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <SDL2/SDL.h>
#include <vector>
#include <array>

#define GRID_SIZE 32
#define HEIGHT 21
#define WIDTH 12

struct Node {
    SDL_Rect m_square;
    int m_rgba[4];
    bool m_open;
};

class GameBoard
{
    public:
    Node m_squares[HEIGHT][WIDTH];
    GameBoard();
    int getHeight();
    int getWidth();
    Node getSquare(int i, int j);
    void setSquareColor(int i, int j, int rgba[4]);
    void closeSquare(int i, int j);
};

#endif