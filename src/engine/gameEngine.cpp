#include "gameEngine.hpp"

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

bool GameEngine::isGameOver() const
{
    return gameOver_;
}

void GameEngine::setGameOver(bool gameOver)
{
    gameOver_ = gameOver;
}