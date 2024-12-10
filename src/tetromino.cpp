#include <SDL2/SDL.h>
#include <iostream>
#include "Tetromino.hpp"

#define GRID_SIZE 32

Tetromino::Tetromino(int x, int y, int theta)
    : m_x{x}, m_y{y}, m_theta{theta}
{
    m_stuck = false;
}

int Tetromino::getX()
{
    return m_x;
}

void Tetromino::setX(int x)
{
    m_x = x;
}

int Tetromino::getY()
{
    return m_y;
}

void Tetromino::setY(int y)
{
    m_y = y;
}
int Tetromino::getTheta()
{
    return m_theta;
}

void Tetromino::setTheta(int theta)
{
    m_theta = theta;
}

SDL_Rect *Tetromino::getBlocks()
{
    return m_blocks;
}

void Tetromino::setBlocks(SDL_Rect rects[4])
{
    for (int i = 0; i < 4; i++)
    {
        m_blocks[i] = rects[i];
    };
}

int *Tetromino::getColor()
{
    return m_rgba;
}

void Tetromino::setColor(int rgba[4])
{

    for (int i = 0; i < 4; i++)
    {
        m_rgba[i] = rgba[i];
    }
}

void Tetromino::moveLeft(GameBoard board)
{
    bool canMove = true;
    for (int i = 0; i < 4; i++)
    {
        int boardY = (m_blocks[i].y - 64) / GRID_SIZE;
        int boardX = (m_blocks[i].x - 32) / GRID_SIZE;
        if (!board.m_squares[boardY][boardX - 1].m_open)
        {
            canMove = false;
            break;
        }
    }
    if (canMove)
    {

        m_x -= GRID_SIZE;
        for (int i = 0; i < 4; i++)
        {
            m_blocks[i].x -= GRID_SIZE;
        }
    }
}
void Tetromino::moveDown(GameBoard board)
{
    bool canMove = true;
    for (int i = 0; i < 4; i++)
    {
        int boardY = (m_blocks[i].y - 64) / GRID_SIZE;
        int boardX = (m_blocks[i].x - 32) / GRID_SIZE;
        if (!board.m_squares[boardY + 1][boardX].m_open)
        {
            canMove = false;
            break;
        }
    }
    if (canMove)
    {
        m_y += GRID_SIZE;
        for (int i = 0; i < 4; i++)
        {
            m_blocks[i].y += GRID_SIZE;
        }
    }
    else
    {
        m_stuck = true;
    }
}
void Tetromino::moveRight(GameBoard board)
{
    bool canMove = true;
    for (int i = 0; i < 4; i++)
    {
        int boardY = (m_blocks[i].y - 64) / GRID_SIZE;
        int boardX = (m_blocks[i].x - 32) / GRID_SIZE;
        if (!board.m_squares[boardY][boardX + 1].m_open)
        {
            canMove = false;
            break;
        }
    }
    if (canMove)
    {
        m_x += GRID_SIZE;
        for (int i = 0; i < 4; i++)
        {
            m_blocks[i].x += GRID_SIZE;
        }
    }
}

bool Tetromino::isStuck()
{
    return m_stuck;
}

// ITetromino subclass definitions
ITetromino::ITetromino(int x, int y, int theta) : Tetromino(x, y, theta)
{
    // assign rectangles
    SDL_Rect rects[4] = {{x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + 3 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE}};
    this->setBlocks(rects);
    // assign color
    int rgba[4] = {255, 0, 0, 255};
    this->setColor(rgba);
}

void ITetromino::rotate(GameBoard board)
{
    std::cout << "rotate i\n";
    int x = this->getX();
    int y = this->getY();
    int theta = this->getTheta();
    SDL_Rect rects[4];

    // add 90deg to theta
    theta = (theta + 90) % 360;
    switch (theta)
    {
    case 0:
        rects[0] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 3 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 90:
        rects[0] = {x + 2 * GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + 3 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 180:
        rects[0] = {x, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 3 * GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 270:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + 3 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    default:
        rects[0] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 3 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    }
    bool canRotate = true;
    for (SDL_Rect re : rects)
    {
        int boardX = (re.x - 32) / GRID_SIZE;
        int boardY = (re.y - 64) / GRID_SIZE;
        if (!board.m_squares[boardY][boardX].m_open)
        {
            canRotate = false;
        }
    }
    if (canRotate)
    {
        this->setTheta(theta);
        this->setBlocks(rects);
    }
}

JTetromino::JTetromino(int x, int y, int theta) : Tetromino(x, y, theta)
{
    // assign rectangles
    SDL_Rect rects[4] = {{x, y, GRID_SIZE, GRID_SIZE},
                         {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE}};
    this->setBlocks(rects);
    // assign color
    int rgba[4] = {0, 255, 0, 255};
    this->setColor(rgba);
}
void JTetromino::rotate(GameBoard board)
{
    std::cout << "rotate j\n";

    int x = this->getX();
    int y = this->getY();
    int theta = this->getTheta();
    SDL_Rect rects[4];

    // add 90deg to theta
    theta = (theta + 90) % 360;
    switch (theta)
    {
    case 0:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 90:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + 2 * GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 180:
        rects[0] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 270:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    default:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    }
    bool canRotate = true;
    for (SDL_Rect re : rects)
    {
        int boardX = (re.x - 32) / GRID_SIZE;
        int boardY = (re.y - 64) / GRID_SIZE;
        if (!board.m_squares[boardY][boardX].m_open)
        {
            canRotate = false;
        }
    }
    if (canRotate)
    {
        this->setTheta(theta);
        this->setBlocks(rects);
    }
}

LTetromino::LTetromino(int x, int y, int theta) : Tetromino(x, y, theta)
{
    // assign rectangles
    SDL_Rect rects[4] = {{x + 2 * GRID_SIZE, y, GRID_SIZE, GRID_SIZE},
                         {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE}};
    this->setBlocks(rects);
    // set color
    int rgba[4] = {0, 0, 255, 255};
    this->setColor(rgba);
}
void LTetromino::rotate(GameBoard board)
{
    std::cout << "rotate l\n";

    int x = this->getX();
    int y = this->getY();
    int theta = this->getTheta();
    SDL_Rect rects[4];

    // add 90deg to theta
    theta = (theta + 90) % 360;
    switch (theta)
    {
    case 0:
        rects[0] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        break;
    case 90:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 180:
        rects[0] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 270:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    default:
        rects[0] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        break;
    }
    bool canRotate = true;
    for (SDL_Rect re : rects)
    {
        int boardX = (re.x - 32) / GRID_SIZE;
        int boardY = (re.y - 64) / GRID_SIZE;
        if (!board.m_squares[boardY][boardX].m_open)
        {
            canRotate = false;
        }
    }
    if (canRotate)
    {
        this->setTheta(theta);
        this->setBlocks(rects);
    }
}

OTetromino::OTetromino(int x, int y, int theta) : Tetromino(x, y, theta)
{
    // assign rectangles
    SDL_Rect rects[4] = {{x, y, GRID_SIZE, GRID_SIZE},
                         {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE},
                         {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE}};
    this->setBlocks(rects);
    // assign color
    int rgba[4] = {0, 255, 255, 255};
    this->setColor(rgba);
}

void OTetromino::rotate(GameBoard board)
{
    std::cout << "rotate 0\n";

    int x = this->getX();
    int y = this->getY();
    int theta = this->getTheta();
    SDL_Rect rects[4];

    // add 90deg to theta
    theta = (theta + 90) % 360;
    switch (theta)
    {
    case 0:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[2] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 90:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[2] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 180:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[2] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 270:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[2] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    default:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[2] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    }
    bool canRotate = true;
    for (SDL_Rect re : rects)
    {
        int boardX = (re.x - 32) / GRID_SIZE;
        int boardY = (re.y - 64) / GRID_SIZE;
        if (!board.m_squares[boardY][boardX].m_open)
        {
            canRotate = false;
        }
    }
    if (canRotate)
    {
        this->setTheta(theta);
        this->setBlocks(rects);
    }
}

STetromino::STetromino(int x, int y, int theta) : Tetromino(x, y, theta)
{
    // assign rectangles
    SDL_Rect rects[4] = {{x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE},
                         {x + 2 * GRID_SIZE, y, GRID_SIZE, GRID_SIZE},
                         {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE}};
    this->setBlocks(rects);
    // assign color
    int rgba[4] = {255, 0, 255, 255};
    this->setColor(rgba);
}

void STetromino::rotate(GameBoard board)
{
    std::cout << "rotate s\n";

    int x = this->getX();
    int y = this->getY();
    int theta = this->getTheta();
    SDL_Rect rects[4];

    // add 90deg to theta
    theta = (theta + 90) % 360;
    switch (theta)
    {
    case 0:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + 2 * GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[2] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 90:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 180:
        rects[0] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 270:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    default:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + 2 * GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[2] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    }
    bool canRotate = true;
    for (SDL_Rect re : rects)
    {
        int boardX = (re.x - 32) / GRID_SIZE;
        int boardY = (re.y - 64) / GRID_SIZE;
        if (!board.m_squares[boardY][boardX].m_open)
        {
            canRotate = false;
        }
    }
    if (canRotate)
    {
        this->setTheta(theta);
        this->setBlocks(rects);
    }
}

TTetromino::TTetromino(int x, int y, int theta) : Tetromino(x, y, theta)
{
    // assign rectangles
    SDL_Rect rects[4] = {{x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE},
                         {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE}};
    this->setBlocks(rects);
    // assign color
    int rgba[4] = {255, 255, 0, 255};
    this->setColor(rgba);
}

void TTetromino::rotate(GameBoard board)
{
    std::cout << "rotate t\n";

    int x = this->getX();
    int y = this->getY();
    int theta = this->getTheta();
    SDL_Rect rects[4];

    // add 90deg to theta
    theta = (theta + 90) % 360;
    switch (theta)
    {
    case 0:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 90:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 180:
        rects[0] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 270:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    default:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    }
    bool canRotate = true;
    for (SDL_Rect re : rects)
    {
        int boardX = (re.x - 32) / GRID_SIZE;
        int boardY = (re.y - 64) / GRID_SIZE;
        if (!board.m_squares[boardY][boardX].m_open)
        {
            canRotate = false;
        }
    }
    if (canRotate)
    {
        this->setTheta(theta);
        this->setBlocks(rects);
    }
}

ZTetromino::ZTetromino(int x, int y, int theta) : Tetromino(x, y, theta)
{
    // assign rectangles
    SDL_Rect rects[4] = {{x, y, GRID_SIZE, GRID_SIZE},
                         {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE},
                         {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE},
                         {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE}};
    this->setBlocks(rects);
    // assign color
    int rgba[4] = {165, 165, 0, 255};
    this->setColor(rgba);
}

void ZTetromino::rotate(GameBoard board)
{
    std::cout << "rotate z\n";

    int x = this->getX();
    int y = this->getY();
    int theta = this->getTheta();
    SDL_Rect rects[4];

    // add 90deg to theta
    theta = (theta + 90) % 360;
    switch (theta)
    {
    case 0:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 90:
        rects[0] = {x + 2 * GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 180:
        rects[0] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[1] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    case 270:
        rects[0] = {x + GRID_SIZE, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x, y + 2 * GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    default:
        rects[0] = {x, y, GRID_SIZE, GRID_SIZE};
        rects[1] = {x, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[2] = {x + GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        rects[3] = {x + 2 * GRID_SIZE, y + GRID_SIZE, GRID_SIZE, GRID_SIZE};
        break;
    }
    bool canRotate = true;
    for (SDL_Rect re : rects)
    {
        int boardX = (re.x - 32) / GRID_SIZE;
        int boardY = (re.y - 64) / GRID_SIZE;
        if (!board.m_squares[boardY][boardX].m_open)
        {
            canRotate = false;
        }
    }
    if (canRotate)
    {
        this->setTheta(theta);
        this->setBlocks(rects);
    }
}