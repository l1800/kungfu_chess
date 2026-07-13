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

    static std::set<Position> bishopDestinations(
        const Board& board,
        const Piece& piece
    );

    static std::set<Position> queenDestinations(
        const Board& board,
        const Piece& piece
    );

    static std::set<Position> knightDestinations(
        const Board& board,
        const Piece& piece
    );

    static std::set<Position> kingDestinations(
        const Board& board,
        const Piece& piece
    );

    static std::set<Position> pawnDestinations(
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

    static void addIfAvailable(
        const Board& board,
        const Piece& piece,
        const Position& destination,
        std::set<Position>& destinations
    );
};