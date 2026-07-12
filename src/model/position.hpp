#pragma once

#include <string>


class Position
{
public:

    Position(int row, int col);

    int row() const;
    int col() const;


    bool operator==(const Position& other) const;


private:

    int m_row;
    int m_col;
};