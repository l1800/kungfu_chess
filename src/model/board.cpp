#include "Board.hpp"


Board::Board(int width, int height)
    :
    m_width(width),
    m_height(height),
    m_cells(
        height,
        std::vector<std::string>(width, ".")
    )
{
}


int Board::width() const
{
    return m_width;
}


int Board::height() const
{
    return m_height;
}


void Board::setCell(
    int row,
    int col,
    const std::string& value
)
{
    m_cells[row][col] = value;
}


std::string Board::getCell(
    int row,
    int col
) const
{
    return m_cells[row][col];
}