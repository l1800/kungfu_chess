#include "ruleEngine.hpp"

#include "pieceRules.hpp"

MoveValidation RuleEngine::validateMove(
    const Board& board,
    const Position& source,
    const Position& destination
) const
{
    if (!board.isInside(source) ||
        !board.isInside(destination))
    {
        return { false, "outside_board" };
    }

    const Piece* sourcePiece =
        board.getPieceAt(source);

    if (sourcePiece == nullptr)
    {
        return { false, "empty_source" };
    }

    const Piece* destinationPiece =
        board.getPieceAt(destination);

    if (destinationPiece != nullptr &&
        destinationPiece->color() == sourcePiece->color())
    {
        return { false, "friendly_destination" };
    }

    const std::set<Position> legalDestinations =
        PieceRules::legalDestinations(
            board,
            *sourcePiece
        );

    if (legalDestinations.count(destination) == 0)
    {
        return { false, "illegal_piece_move" };
    }

    return { true, "ok" };
}