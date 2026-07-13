#pragma once

#include "boardMapper.hpp"

#include "../engine/gameEngine.hpp"
#include "../model/board.hpp"

#include <optional>

class Controller
{
public:
    Controller(
        const Board& board,
        const BoardMapper& mapper,
        GameEngine& gameEngine
    );

    void click(int x, int y);

    const std::optional<Position>& selectedCell() const;

private:
    const Board& board_;
    const BoardMapper& mapper_;
    GameEngine& gameEngine_;

    std::optional<Position> selectedCell_;
};