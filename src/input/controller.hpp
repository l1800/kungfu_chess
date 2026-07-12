#pragma once

#include "boardMapper.hpp"

#include "../engine/moveRequester.hpp"
#include "../model/board.hpp"

#include <optional>

class Controller
{
public:
    Controller(
        const Board& board,
        const BoardMapper& mapper,
        MoveRequester& moveRequester
    );

    void click(int x, int y);

    const std::optional<Position>& selectedCell() const;

private:
    const Board& board_;
    const BoardMapper& mapper_;
    MoveRequester& moveRequester_;

    std::optional<Position> selectedCell_;
};