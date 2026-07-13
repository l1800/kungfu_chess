#pragma once

#include "../model/board.hpp"
#include "../model/position.hpp"
#include "../realtime/realTimeArbiter.hpp"
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
        RuleEngine& ruleEngine,
        RealTimeArbiter& realTimeArbiter
    );

    virtual ~GameEngine() = default;

    virtual MoveResult requestMove(
        const Position& source,
        const Position& destination
    );

    virtual void wait(int milliseconds);

    bool isGameOver() const;
    void setGameOver(bool gameOver);

private:
    Board& board_;
    RuleEngine& ruleEngine_;
    RealTimeArbiter& realTimeArbiter_;

    bool gameOver_;
};