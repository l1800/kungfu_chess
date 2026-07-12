#include "rookRule.hpp"

#include <stdexcept>

std::set<Position> RookRule::legalDestinations(
    const Board& board,
    const Piece& piece
)
{
    if (piece.kind() != PieceKind::Rook)
    {
        throw std::invalid_argument(
            "piece_is_not_rook"
        );
    }

    std::set<Position> destinations;

    addDirection(
        board,
        piece,
        -1,
        0,
        destinations
    );

    addDirection(
        board,
        piece,
        1,
        0,
        destinations
    );

    addDirection(
        board,
        piece,
        0,
        -1,
        destinations
    );

    addDirection(
        board,
        piece,
        0,
        1,
        destinations
    );

    return destinations;
}

void RookRule::addDirection(
    const Board& board,
    const Piece& piece,
    int rowStep,
    int colStep,
    std::set<Position>& destinations
)
{
    int row =
        piece.cell().row() + rowStep;

    int col =
        piece.cell().col() + colStep;

    while (board.isInside(Position(row, col)))
    {
        const Position destination(row, col);

        const Piece* blockingPiece =
            board.getPieceAt(destination);

        if (blockingPiece == nullptr)
        {
            destinations.insert(destination);

            row += rowStep;
            col += colStep;

            continue;
        }

        if (blockingPiece->color() != piece.color())
        {
            destinations.insert(destination);
        }

        break;
    }
}