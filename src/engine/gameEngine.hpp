#pragma once

#include "../model/board.hpp"
#include "../model/position.hpp"
#include "../rules/ruleEngine.hpp"

#include <string>

struct MoveResult
{
    bool isAccepted;
    std::string reason;
};

class GameEngine
{
public:
    GameEngine(
        Board& board,
        RuleEngine& ruleEngine
    );

    virtual ~GameEngine() = default;

    virtual MoveResult requestMove(
        const Position& source,
        const Position& destination
    );

    bool isGameOver() const;

    void setGameOver(bool gameOver);

private:
    Board& board_;
    RuleEngine& ruleEngine_;
    bool gameOver_;
};