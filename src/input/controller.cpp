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

    selectedCell_.reset();

    const MoveResult result =
        gameEngine_.requestMove(
            source,
            destination
        );

    (void)result;
}

const std::optional<Position>&
Controller::selectedCell() const
{
    return selectedCell_;
}