#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL2/SDL.h>
#include "GameBoard.hpp"

#define GRID_SIZE 32

class Tetromino {

    public:
    Tetromino(int x, int y, int theta);
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    int getTheta();
    void setTheta(int theta);
    SDL_Rect* getBlocks();
    void setBlocks(SDL_Rect rects[4]);
    virtual void rotate() = 0;
    void moveLeft(GameBoard board);
    void moveDown(GameBoard board);
    void moveRight(GameBoard board);
    bool isStuck();
    
    private:
    bool m_stuck;
    int m_x;
    int m_y;
    int m_theta;
    SDL_Rect m_blocks[4];
};

class ITetromino : public Tetromino {
    
    public:
    ITetromino(int x, int y, int theta);
    void rotate() override;

};

class JTetromino : public Tetromino {

    public:
    JTetromino(int x, int y, int theta);
    void rotate() override;

};

class LTetromino : public Tetromino {

    public:
    LTetromino(int x, int y, int theta);
    void rotate() override;

};

class OTetromino : public Tetromino {

    public:
    OTetromino(int x, int y, int theta);
    void rotate() override;

};

class STetromino : public Tetromino {

    public:
    STetromino(int x, int y, int theta);
    void rotate() override;

};

class TTetromino : public Tetromino {

    public:
    TTetromino(int x, int y, int theta);
    void rotate() override;

};

class ZTetromino : public Tetromino {

    public:
    ZTetromino(int x, int y, int theta);
    void rotate() override;

};
#endif