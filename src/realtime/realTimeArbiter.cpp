#include "realTimeArbiter.hpp"

#include <stdexcept>

RealTimeArbiter::RealTimeArbiter(Board& board)
    : board_(board)
{
}

bool RealTimeArbiter::hasActiveMotion() const
{
    return activeMotion_.has_value();
}

void RealTimeArbiter::startMotion(
    const Position& source,
    const Position& destination
)
{
    if (hasActiveMotion())
    {
        throw std::logic_error(
            "motion_already_active"
        );
    }

    Piece* piece = board_.getPieceAt(source);

    if (piece == nullptr)
    {
        throw std::invalid_argument(
            "empty_source"
        );
    }

    piece->setState(PieceState::Moving);

    activeMotion_.emplace(
        piece->id(),
        source,
        destination
    );
}

void RealTimeArbiter::advanceTime(int milliseconds)
{
    if (milliseconds < 0)
    {
        throw std::invalid_argument(
            "milliseconds_must_be_non_negative"
        );
    }

    if (!activeMotion_.has_value())
    {
        return;
    }

    activeMotion_->advance(milliseconds);

    if (activeMotion_->isComplete())
    {
        completeActiveMotion();
    }
}

const std::optional<Motion>&
RealTimeArbiter::activeMotion() const
{
    return activeMotion_;
}

void RealTimeArbiter::completeActiveMotion()
{
    if (!activeMotion_.has_value())
    {
        return;
    }

    const Position source =
        activeMotion_->source();

    const Position destination =
        activeMotion_->destination();

    /*
     * באיטרציה 5 היעד חייב להיות ריק.
     * אכילה תתווסף באיטרציה 6.
     */
    board_.movePiece(source, destination);

    Piece* arrivedPiece =
        board_.getPieceAt(destination);

    if (arrivedPiece == nullptr)
    {
        throw std::logic_error(
            "arrived_piece_missing"
        );
    }

    arrivedPiece->setState(PieceState::Idle);

    activeMotion_.reset();
}