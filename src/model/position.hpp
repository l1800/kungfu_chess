#pragma once

#include <ostream>

class Position
{
public:
    Position(int row, int col);

    int row() const;
    int col() const;

    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

private:
    int row_;
    int col_;
};

std::ostream& operator<<(std::ostream& output, const Position& position);