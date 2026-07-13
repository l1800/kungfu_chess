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

    case PieceKind::Bishop:
        return bishopDestinations(board, piece);

    case PieceKind::Queen:
        return queenDestinations(board, piece);

    case PieceKind::Knight:
        return knightDestinations(board, piece);

    case PieceKind::King:
        return kingDestinations(board, piece);

    case PieceKind::Pawn:
        return pawnDestinations(board, piece);
    }

    return {};
}

std::set<Position> PieceRules::rookDestinations(
    const Board& board,
    const Piece& piece
)
{
    std::set<Position> destinations;

    addSlidingDirection(
        board,
        piece,
        -1,
        0,
        destinations
    );

    addSlidingDirection(
        board,
        piece,
        1,
        0,
        destinations
    );

    addSlidingDirection(
        board,
        piece,
        0,
        -1,
        destinations
    );

    addSlidingDirection(
        board,
        piece,
        0,
        1,
        destinations
    );

    return destinations;
}

std::set<Position> PieceRules::bishopDestinations(
    const Board& board,
    const Piece& piece
)
{
    std::set<Position> destinations;

    addSlidingDirection(
        board,
        piece,
        -1,
        -1,
        destinations
    );

    addSlidingDirection(
        board,
        piece,
        -1,
        1,
        destinations
    );

    addSlidingDirection(
        board,
        piece,
        1,
        -1,
        destinations
    );

    addSlidingDirection(
        board,
        piece,
        1,
        1,
        destinations
    );

    return destinations;
}

std::set<Position> PieceRules::queenDestinations(
    const Board& board,
    const Piece& piece
)
{
    std::set<Position> destinations =
        rookDestinations(board, piece);

    const std::set<Position> bishopMoves =
        bishopDestinations(board, piece);

    destinations.insert(
        bishopMoves.begin(),
        bishopMoves.end()
    );

    return destinations;
}

std::set<Position> PieceRules::knightDestinations(
    const Board& board,
    const Piece& piece
)
{
    static const int offsets[][2] = {
        {-2, -1},
        {-2, 1},
        {-1, -2},
        {-1, 2},
        {1, -2},
        {1, 2},
        {2, -1},
        {2, 1}
    };

    std::set<Position> destinations;

    for (const auto& offset : offsets)
    {
        const Position destination(
            piece.cell().row() + offset[0],
            piece.cell().col() + offset[1]
        );

        addIfAvailable(
            board,
            piece,
            destination,
            destinations
        );
    }

    return destinations;
}

std::set<Position> PieceRules::kingDestinations(
    const Board& board,
    const Piece& piece
)
{
    std::set<Position> destinations;

    for (int rowStep = -1; rowStep <= 1; ++rowStep)
    {
        for (int colStep = -1; colStep <= 1; ++colStep)
        {
            if (rowStep == 0 && colStep == 0)
            {
                continue;
            }

            const Position destination(
                piece.cell().row() + rowStep,
                piece.cell().col() + colStep
            );

            addIfAvailable(
                board,
                piece,
                destination,
                destinations
            );
        }
    }

    return destinations;
}

std::set<Position> PieceRules::pawnDestinations(
    const Board& board,
    const Piece& piece
)
{
    std::set<Position> destinations;

    const int rowStep =
        piece.color() == PieceColor::White
        ? -1
        : 1;

    const Position forward(
        piece.cell().row() + rowStep,
        piece.cell().col()
    );

    /*
     * רגלי מתקדם קדימה רק לתא ריק.
     */
    if (board.isInside(forward) &&
        board.getPieceAt(forward) == nullptr)
    {
        destinations.insert(forward);
    }

    /*
     * רגלי אוכל רק באלכסון קדימה.
     */
    for (const int colStep : {-1, 1})
    {
        const Position diagonal(
            piece.cell().row() + rowStep,
            piece.cell().col() + colStep
        );

        if (!board.isInside(diagonal))
        {
            continue;
        }

        const Piece* target =
            board.getPieceAt(diagonal);

        if (target != nullptr &&
            target->color() != piece.color())
        {
            destinations.insert(diagonal);
        }
    }

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
    int row =
        piece.cell().row() + rowStep;

    int col =
        piece.cell().col() + colStep;

    while (board.isInside(Position(row, col)))
    {
        const Position destination(row, col);

        const Piece* blocker =
            board.getPieceAt(destination);

        if (blocker == nullptr)
        {
            destinations.insert(destination);

            row += rowStep;
            col += colStep;

            continue;
        }

        /*
         * כלי אויב הוא יעד חוקי,
         * אך לא ניתן לעבור דרכו.
         */
        if (blocker->color() != piece.color())
        {
            destinations.insert(destination);
        }

        break;
    }
}

void PieceRules::addIfAvailable(
    const Board& board,
    const Piece& piece,
    const Position& destination,
    std::set<Position>& destinations
)
{
    if (!board.isInside(destination))
    {
        return;
    }

    const Piece* target =
        board.getPieceAt(destination);

    if (target == nullptr ||
        target->color() != piece.color())
    {
        destinations.insert(destination);
    }
}