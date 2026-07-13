#include "controller.hpp"

Controller::Controller(
    const Board& board,
    const BoardMapper& mapper,
    GameEngine& gameEngine
)
    : board_(board),
    mapper_(mapper),
    gameEngine_(gameEngine)
{
}

void Controller::click(int x, int y)
{
    const std::optional<Position> clickedCell =
        mapper_.pixelToCell(x, y);

    if (!clickedCell.has_value())
    {
        selectedCell_.reset();
        return;
    }

    if (!selectedCell_.has_value())
    {
        if (board_.getPieceAt(clickedCell.value()) != nullptr)
        {
            selectedCell_ = clickedCell;
        }

        return;
    }

    const Position source = selectedCell_.value();
    const Position destination = clickedCell.value();

    const Piece* sourcePiece =
        board_.getPieceAt(source);

    if (sourcePiece == nullptr)
    {
        selectedCell_.reset();
        return;
    }

    const Piece* destinationPiece =
        board_.getPieceAt(destination);

    if (destinationPiece != nullptr &&
        destinationPiece->color() ==
        sourcePiece->color())
    {
        selectedCell_ = destination;
        return;
    }

    const MoveResult result =
        gameEngine_.requestMove(
            source,
            destination
        );

    if (result.isAccepted)
    {
        selectedCell_.reset();
        return;
    }

    selectedCell_ = source;
}

void Controller::jump(int x, int y)
{
    const std::optional<Position> clickedCell =
        mapper_.pixelToCell(x, y);

    if (!clickedCell.has_value())
    {
        return;
    }

    (void)gameEngine_.jump(clickedCell.value());
}

const std::optional<Position>&
Controller::selectedCell() const
{
    return selectedCell_;
}