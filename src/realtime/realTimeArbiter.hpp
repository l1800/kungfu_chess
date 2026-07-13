#pragma once

#include "motion.hpp"

#include "../model/board.hpp"

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

    ArrivalEvents advanceTime(int milliseconds);

    const std::optional<Motion>& activeMotion() const;

private:
    ArrivalEvents completeActiveMotion();

    Board& board_;
    std::optional<Motion> activeMotion_;
};