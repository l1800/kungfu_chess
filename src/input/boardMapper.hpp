#pragma once

#include "../model/position.hpp"

#include <optional>

class BoardMapper
{
public:
    static constexpr int CELL_SIZE = 100;

    BoardMapper(int boardWidth, int boardHeight);

    std::optional<Position> pixelToCell(int x, int y) const;

private:
    int boardWidth_;
    int boardHeight_;
};