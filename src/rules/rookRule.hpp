#pragma once

#include "../model/board.hpp"
#include "../model/piece.hpp"
#include "../model/position.hpp"

#include <set>

class RookRule
{
public:
    static std::set<Position> legalDestinations(
        const Board& board,
        const Piece& piece
    );

private:
    static void addDirection(
        const Board& board,
        const Piece& piece,
        int rowStep,
        int colStep,
        std::set<Position>& destinations
    );
};