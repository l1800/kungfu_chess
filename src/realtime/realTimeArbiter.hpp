#pragma once

#include "motion.hpp"

#include "../model/board.hpp"

#include <optional>

class RealTimeArbiter
{
public:
    explicit RealTimeArbiter(Board& board);

    bool hasActiveMotion() const;

    void startMotion(
        const Position& source,
        const Position& destination
    );

    void advanceTime(int milliseconds);

    const std::optional<Motion>&
        activeMotion() const;

private:
    void completeActiveMotion();

    Board& board_;
    std::optional<Motion> activeMotion_;
};