#pragma once

#include "board.hpp"
#include "gameSnapshot.hpp"
#include "position.hpp"
#include "realTimeArbiter.hpp"
#include "ruleEngine.hpp"

#include <optional>
#include <string>

struct MoveResult
{
    bool isAccepted;
    std::string reason;
};

class GameEngine
{
public:
    static constexpr int CELL_SIZE = 100;

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

    virtual MoveResult jump(const Position& cell);

    virtual void wait(int milliseconds);

    GameSnapshot snapshot() const;

    GameSnapshot snapshot(
        const std::optional<Position>& selectedCell
    ) const;

    bool isGameOver() const;
    void setGameOver(bool gameOver);

private:
    PieceSnapshot createPieceSnapshot(
        const Piece& piece
    ) const;

    Board& board_;
    RuleEngine& ruleEngine_;
    RealTimeArbiter& realTimeArbiter_;

    bool gameOver_;
};