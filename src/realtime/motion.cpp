#include "motion.hpp"

#include <algorithm>
#include <cstdlib>
#include <stdexcept>

Motion::Motion(
    int pieceId,
    const Position& source,
    const Position& destination
)
    : pieceId_(pieceId),
    source_(source),
    destination_(destination),
    elapsedMs_(0),
    durationMs_(
        calculateDurationMs(source, destination)
    )
{
    if (pieceId < 0)
    {
        throw std::invalid_argument(
            "piece_id_must_be_non_negative"
        );
    }

    if (source == destination)
    {
        throw std::invalid_argument(
            "motion_requires_different_cells"
        );
    }
}

int Motion::pieceId() const
{
    return pieceId_;
}

const Position& Motion::source() const
{
    return source_;
}

const Position& Motion::destination() const
{
    return destination_;
}

int Motion::elapsedMs() const
{
    return elapsedMs_;
}

int Motion::durationMs() const
{
    return durationMs_;
}

bool Motion::isComplete() const
{
    return elapsedMs_ >= durationMs_;
}

void Motion::advance(int milliseconds)
{
    if (milliseconds < 0)
    {
        throw std::invalid_argument(
            "milliseconds_must_be_non_negative"
        );
    }

    elapsedMs_ = std::min(
        elapsedMs_ + milliseconds,
        durationMs_
    );
}

int Motion::calculateDurationMs(
    const Position& source,
    const Position& destination
)
{
    const int rowDistance =
        std::abs(destination.row() - source.row());

    const int colDistance =
        std::abs(destination.col() - source.col());

    const int cellSteps =
        std::max(rowDistance, colDistance);

    return cellSteps * 1000;
}