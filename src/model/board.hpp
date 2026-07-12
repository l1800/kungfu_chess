#pragma once

#include <vector>
#include <string>


class Board
{
public:

    Board(int width, int height);

    int width() const;
    int height() const;

    void setCell(
        int row,
        int col,
        const std::string& value
    );

    std::string getCell(
        int row,
        int col
    ) const;


private:

    int m_width;
    int m_height;

    std::vector<std::vector<std::string>> m_cells;
};