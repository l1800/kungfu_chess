#include "pieceRules.hpp"

std::set<Position> PieceRules::legalDestinations(
    const Board& board,
    const Piece& piece
)
{
    switch (piece.kind())
    {
    case PieceKind::Rook:
        return rookDestinations(board, piece);

    default:
        return {};
    }
}

std::set<Position> PieceRules::rookDestinations(
    const Board& board,
    const Piece& piece
)
{
    std::set<Position> destinations;

    addSlidingDirection(board, piece, -1, 0, destinations);
    addSlidingDirection(board, piece, 1, 0, destinations);
    addSlidingDirection(board, piece, 0, -1, destinations);
    addSlidingDirection(board, piece, 0, 1, destinations);

    return destinations;
}

void PieceRules::addSlidingDirection(
    const Board& board,
    const Piece& piece,
    int rowStep,
    int colStep,
    std::set<Position>& destinations
)
{
    int row = piece.cell().row() + rowStep;
    int col = piece.cell().col() + colStep;

    while (board.isInside(Position(row, col)))
    {
        const Position destination(row, col);

        const Piece* blockingPiece =
            board.getPieceAt(destination);

        if (blockingPiece == nullptr)
        {
            destinations.insert(destination);
        }
        else
        {
            if (blockingPiece->color() != piece.color())
            {
                destinations.insert(destination);
            }

            break;
        }

        row += rowStep;
        col += colStep;
    }
}