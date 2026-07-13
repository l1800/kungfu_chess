#pragma once

#include "../model/board.hpp"
#include "../model/piece.hpp"
#include "../model/position.hpp"

#include <set>

class PieceRules
{
public:
    static std::set<Position> legalDestinations(
        const Board& board,
        const Piece& piece
    );

private:
    static std::set<Position> rookDestinations(
        const Board& board,
        const Piece& piece
    );

    static void addSlidingDirection(
        const Board& board,
        const Piece& piece,
        int rowStep,
        int colStep,
        std::set<Position>& destinations
    );
};