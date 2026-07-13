#include "gameEngine.hpp"

GameEngine::GameEngine(
    Board& board,
    RuleEngine& ruleEngine
)
    : board_(board),
    ruleEngine_(ruleEngine),
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
        return { false, "game_over" };
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

    // באיטרציה 4 עדיין לא מזיזים את הכלי.
    return { true, "ok" };
}

bool GameEngine::isGameOver() const
{
    return gameOver_;
}

void GameEngine::setGameOver(bool gameOver)
{
    gameOver_ = gameOver;
}