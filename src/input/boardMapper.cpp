#include "boardMapper.hpp"

#include <stdexcept>

BoardMapper::BoardMapper(int boardWidth, int boardHeight)
    : boardWidth_(boardWidth),
    boardHeight_(boardHeight)
{
    if (boardWidth <= 0 || boardHeight <= 0)
    {
        throw std::invalid_argument(
            "board_dimensions_must_be_positive"
        );
    }
}

std::optional<Position> BoardMapper::pixelToCell(
    int x,
    int y
) const
{
    if (x < 0 || y < 0)
    {
        return std::nullopt;
    }

    const int col = x / CELL_SIZE;
    const int row = y / CELL_SIZE;

    if (col >= boardWidth_ || row >= boardHeight_)
    {
        return std::nullopt;
    }

    return Position(row, col);
}