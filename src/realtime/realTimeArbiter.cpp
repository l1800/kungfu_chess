#include "realTimeArbiter.hpp"

#include <stdexcept>
#include <vector>

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

bool RealTimeArbiter::jumpAt(const Position& position)
{
    Piece* piece = board_.getPieceAt(position);

    if (piece == nullptr)
    {
        return false;
    }

    if (piece->state() == PieceState::Moving)
    {
        return false;
    }

    if (piece->state() == PieceState::Airborne)
    {
        piece->setState(PieceState::Idle);
        airborneRemainingMs_.erase(piece->id());
        return true;
    }

    piece->setState(PieceState::Airborne);
    airborneRemainingMs_[piece->id()] = AIRBORNE_DURATION_MS;
    return true;
}

ArrivalEvents RealTimeArbiter::advanceTime(
    int milliseconds
)
{
    if (milliseconds < 0)
    {
        throw std::invalid_argument(
            "milliseconds_must_be_non_negative"
        );
    }

    if (!activeMotion_.has_value())
    {
        advanceAirborneTimers(milliseconds);
        return {};
    }

    activeMotion_->advance(milliseconds);

    if (!activeMotion_->isComplete())
    {
        advanceAirborneTimers(milliseconds);
        return {};
    }

    const ArrivalEvents events = completeActiveMotion();
    advanceAirborneTimers(milliseconds);

    return events;
}

const std::optional<Motion>&
RealTimeArbiter::activeMotion() const
{
    return activeMotion_;
}

ArrivalEvents
RealTimeArbiter::completeActiveMotion()
{
    if (!activeMotion_.has_value())
    {
        return {};
    }

    const Position source =
        activeMotion_->source();

    const Position destination =
        activeMotion_->destination();

    Piece* movingPiece =
        board_.getPieceAt(source);

    if (movingPiece == nullptr)
    {
        throw std::logic_error(
            "moving_piece_missing"
        );
    }

    ArrivalEvents events;
    events.motionCompleted = true;

    Piece* destinationPiece =
        board_.getPieceAt(destination);

    if (destinationPiece != nullptr &&
        destinationPiece->state() != PieceState::Airborne)
    {
        events.pieceCaptured = true;
        events.capturedPieceId =
            destinationPiece->id();

        events.kingCaptured =
            destinationPiece->kind() ==
            PieceKind::King;

        /*
         * �������� 6 ������ ����� �� �����.
         */
        board_.removePiece(destination);
    }

    if (destinationPiece != nullptr &&
        destinationPiece->state() == PieceState::Airborne)
    {
        events.pieceCaptured = true;
        events.capturedPieceId = movingPiece->id();
        events.kingCaptured = movingPiece->kind() == PieceKind::King;

        board_.removePiece(source);

        activeMotion_.reset();

        return events;
    }

    /*
     * ���� ����� ����, ���� ����� �� ����.
     */
    board_.movePiece(
        source,
        destination
    );

    Piece* arrivedPiece =
        board_.getPieceAt(destination);

    if (arrivedPiece == nullptr)
    {
        throw std::logic_error(
            "arrived_piece_missing"
        );
    }

    arrivedPiece->setState(
        PieceState::Idle
    );

    promotePawnIfNeeded(*arrivedPiece);

    activeMotion_.reset();

    return events;
}

void RealTimeArbiter::advanceAirborneTimers(int milliseconds)
{
    std::vector<int> toLand;

    for (auto& entry : airborneRemainingMs_)
    {
        entry.second -= milliseconds;

        if (entry.second <= 0)
        {
            toLand.push_back(entry.first);
        }
    }

    for (const int pieceId : toLand)
    {
        for (int row = 0; row < board_.height(); ++row)
        {
            for (int col = 0; col < board_.width(); ++col)
            {
                Piece* piece =
                    board_.getPieceAt(Position(row, col));

                if (piece != nullptr &&
                    piece->id() == pieceId &&
                    piece->state() == PieceState::Airborne)
                {
                    piece->setState(PieceState::Idle);
                }
            }
        }

        airborneRemainingMs_.erase(pieceId);
    }
}

void RealTimeArbiter::promotePawnIfNeeded(Piece& piece)
{
    if (piece.kind() != PieceKind::Pawn)
    {
        return;
    }

    const int promotionRow =
        piece.color() == PieceColor::White
        ? 0
        : board_.height() - 1;

    if (piece.cell().row() != promotionRow)
    {
        return;
    }

    const Position destination = piece.cell();
    const int id = piece.id();
    const PieceColor color = piece.color();

    board_.removePiece(destination);

    board_.addPiece(
        Piece(
            id,
            color,
            PieceKind::Queen,
            destination
        )
    );
}