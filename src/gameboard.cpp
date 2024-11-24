#include "GameBoard.hpp"

GameBoard::GameBoard()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            m_squares[i][j].m_square = 
            {32 + j * GRID_SIZE, 64 + i * GRID_SIZE, GRID_SIZE, GRID_SIZE};
            if (j == 0 || j == (WIDTH - 1) || i == (HEIGHT - 1))
            {
                m_squares[i][j].m_rgba[0] = 0;
                m_squares[i][j].m_rgba[1] = 0;
                m_squares[i][j].m_rgba[2] = 0;
                m_squares[i][j].m_rgba[3] = 255;
                m_squares[i][j].m_open = false;
            }
            else
            {
                m_squares[i][j].m_rgba[0] = 255;
                m_squares[i][j].m_rgba[1] = 255;
                m_squares[i][j].m_rgba[2] = 255;
                m_squares[i][j].m_rgba[3] = 255;
                m_squares[i][j].m_open = true;
            }
        }
    }
}

int GameBoard::getHeight() {
    return HEIGHT;
}

int GameBoard::getWidth() {
    return WIDTH;
}

Node GameBoard::getSquare(int i, int j) {
    return m_squares[i][j];
}

void GameBoard::setSquareColor(int i, int j, int rgba[4]) {
    for (int k=0; k<4; k++) {
        m_squares[i][j].m_rgba[k] = rgba[k];
    }
}

void GameBoard::closeSquare(int i, int j) {
    m_squares[i][j].m_open = false;
}