#include "gameEngine.hpp"

#include <algorithm>

GameEngine::GameEngine(
    Board& board,
    RuleEngine& ruleEngine,
    RealTimeArbiter& realTimeArbiter
)
    : board_(board),
    ruleEngine_(ruleEngine),
    realTimeArbiter_(realTimeArbiter),
    gameOver_(false)
{
}

MoveResult GameEngine::requestMove(
    const Position& source,
    const Position& destination
)
{
    if (gameOver_)
    {
        return {
            false,
            "game_over"
        };
    }

    if (realTimeArbiter_.hasActiveMotion())
    {
        return {
            false,
            "motion_in_progress"
        };
    }

    const MoveValidation validation =
        ruleEngine_.validateMove(
            board_,
            source,
            destination
        );

    if (!validation.isValid)
    {
        return {
            false,
            validation.reason
        };
    }

    realTimeArbiter_.startMotion(
        source,
        destination
    );

    return {
        true,
        "ok"
    };
}

void GameEngine::wait(int milliseconds)
{
    const ArrivalEvents events =
        realTimeArbiter_.advanceTime(
            milliseconds
        );

    if (events.kingCaptured)
    {
        gameOver_ = true;
    }
}

GameSnapshot GameEngine::snapshot() const
{
    return snapshot(std::nullopt);
}

GameSnapshot GameEngine::snapshot(
    const std::optional<Position>& selectedCell
) const
{
    GameSnapshot result{
        board_.width(),
        board_.height(),
        CELL_SIZE,
        {},
        selectedCell,
        gameOver_
    };

    for (int row = 0; row < board_.height(); ++row)
    {
        for (int col = 0; col < board_.width(); ++col)
        {
            const Piece* piece =
                board_.getPieceAt(
                    Position(row, col)
                );

            if (piece == nullptr)
            {
                continue;
            }

            result.pieces.push_back(
                createPieceSnapshot(*piece)
            );
        }
    }

    return result;
}

PieceSnapshot GameEngine::createPieceSnapshot(
    const Piece& piece
) const
{
    double pixelX =
        static_cast<double>(
            piece.cell().col() * CELL_SIZE
            );

    double pixelY =
        static_cast<double>(
            piece.cell().row() * CELL_SIZE
            );

    const std::optional<Motion>& activeMotion =
        realTimeArbiter_.activeMotion();

    if (activeMotion.has_value() &&
        activeMotion->pieceId() == piece.id())
    {
        const double duration =
            static_cast<double>(
                activeMotion->durationMs()
                );

        double progress = 1.0;

        if (duration > 0.0)
        {
            progress =
                static_cast<double>(
                    activeMotion->elapsedMs()
                    ) / duration;
        }

        progress = std::clamp(
            progress,
            0.0,
            1.0
        );

        const double sourceX =
            static_cast<double>(
                activeMotion->source().col() *
                CELL_SIZE
                );

        const double sourceY =
            static_cast<double>(
                activeMotion->source().row() *
                CELL_SIZE
                );

        const double destinationX =
            static_cast<double>(
                activeMotion->destination().col() *
                CELL_SIZE
                );

        const double destinationY =
            static_cast<double>(
                activeMotion->destination().row() *
                CELL_SIZE
                );

        pixelX =
            sourceX +
            (destinationX - sourceX) * progress;

        pixelY =
            sourceY +
            (destinationY - sourceY) * progress;
    }

    return {
        piece.id(),
        piece.color(),
        piece.kind(),
        piece.state(),
        pixelX,
        pixelY
    };
}

bool GameEngine::isGameOver() const
{
    return gameOver_;
}

void GameEngine::setGameOver(bool gameOver)
{
    gameOver_ = gameOver;
}