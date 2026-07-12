#include "position.hpp"

Position::Position(int row, int col)
    : row_(row), col_(col)
{
}

int Position::row() const
{
    return row_;
}

int Position::col() const
{
    return col_;
}

bool Position::operator==(const Position& other) const
{
    return row_ == other.row_ &&
        col_ == other.col_;
}

bool Position::operator!=(const Position& other) const
{
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& output, const Position& position)
{
    output << "Position(row="
        << position.row()
        << ", col="
        << position.col()
        << ")";

    return output;
}