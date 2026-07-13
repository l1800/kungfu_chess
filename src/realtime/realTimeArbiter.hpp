#pragma once

#include "motion.hpp"

#include "../model/board.hpp"

#include <unordered_map>
#include <optional>

struct ArrivalEvents
{
    bool motionCompleted = false;
    bool pieceCaptured = false;
    bool kingCaptured = false;

    std::optional<int> capturedPieceId;
};

class RealTimeArbiter
{
public:
    explicit RealTimeArbiter(Board& board);

    bool hasActiveMotion() const;

    void startMotion(
        const Position& source,
        const Position& destination
    );

    bool jumpAt(const Position& position);

    ArrivalEvents advanceTime(int milliseconds);

    const std::optional<Motion>& activeMotion() const;

private:
    void advanceAirborneTimers(int milliseconds);
    void promotePawnIfNeeded(Piece& piece);

    ArrivalEvents completeActiveMotion();

    Board& board_;
    std::optional<Motion> activeMotion_;
    std::unordered_map<int, int> airborneRemainingMs_;

    static constexpr int AIRBORNE_DURATION_MS = 1000;
};