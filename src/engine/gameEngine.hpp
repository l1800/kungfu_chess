#pragma once

#include "../model/board.hpp"
#include "../model/gameSnapshot.hpp"
#include "../model/position.hpp"
#include "../realtime/realTimeArbiter.hpp"
#include "../rules/ruleEngine.hpp"

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