#include <gtest/gtest.h>

#include "../../src/realtime/realTimeArbiter.hpp"

namespace
{
    void addPiece(
        Board& board,
        int id,
        PieceColor color,
        PieceKind kind,
        const Position& position
    )
    {
        board.addPiece(
            Piece(
                id,
                color,
                kind,
                position
            )
        );
    }
}

TEST(
    RealTimeArbiterTest,
    BoardDoesNotChangeBeforeArrival
)
{
    Board board(3, 3);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Rook,
        Position(0, 0)
    );

    addPiece(
        board,
        2,
        PieceColor::Black,
        PieceKind::Knight,
        Position(0, 1)
    );

    RealTimeArbiter arbiter(board);

    arbiter.startMotion(
        Position(0, 0),
        Position(0, 1)
    );

    const ArrivalEvents events =
        arbiter.advanceTime(999);

    EXPECT_FALSE(events.motionCompleted);
    EXPECT_FALSE(events.pieceCaptured);

    EXPECT_NE(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    EXPECT_NE(
        board.getPieceAt(Position(0, 1)),
        nullptr
    );
}

TEST(
    RealTimeArbiterTest,
    CapturesEnemyOnlyAtArrival
)
{
    Board board(3, 3);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Rook,
        Position(0, 0)
    );

    addPiece(
        board,
        2,
        PieceColor::Black,
        PieceKind::Knight,
        Position(0, 1)
    );

    RealTimeArbiter arbiter(board);

    arbiter.startMotion(
        Position(0, 0),
        Position(0, 1)
    );

    const ArrivalEvents events =
        arbiter.advanceTime(1000);

    EXPECT_TRUE(events.motionCompleted);
    EXPECT_TRUE(events.pieceCaptured);
    EXPECT_FALSE(events.kingCaptured);

    ASSERT_TRUE(
        events.capturedPieceId.has_value()
    );

    EXPECT_EQ(
        events.capturedPieceId.value(),
        2
    );

    EXPECT_EQ(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    const Piece* arrived =
        board.getPieceAt(Position(0, 1));

    ASSERT_NE(arrived, nullptr);
    EXPECT_EQ(arrived->id(), 1);
    EXPECT_EQ(arrived->state(), PieceState::Idle);
}

TEST(
    RealTimeArbiterTest,
    ReportsKingCapture
)
{
    Board board(3, 3);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Rook,
        Position(0, 0)
    );

    addPiece(
        board,
        2,
        PieceColor::Black,
        PieceKind::King,
        Position(0, 2)
    );

    RealTimeArbiter arbiter(board);

    arbiter.startMotion(
        Position(0, 0),
        Position(0, 2)
    );

    const ArrivalEvents events =
        arbiter.advanceTime(2000);

    EXPECT_TRUE(events.motionCompleted);
    EXPECT_TRUE(events.pieceCaptured);
    EXPECT_TRUE(events.kingCaptured);

    const Piece* arrived =
        board.getPieceAt(Position(0, 2));

    ASSERT_NE(arrived, nullptr);
    EXPECT_EQ(arrived->id(), 1);
    EXPECT_EQ(arrived->kind(), PieceKind::Rook);
}

TEST(
    RealTimeArbiterTest,
    EmptyDestinationProducesNoCaptureEvent
)
{
    Board board(3, 3);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Rook,
        Position(0, 0)
    );

    RealTimeArbiter arbiter(board);

    arbiter.startMotion(
        Position(0, 0),
        Position(0, 1)
    );

    const ArrivalEvents events =
        arbiter.advanceTime(1000);

    EXPECT_TRUE(events.motionCompleted);
    EXPECT_FALSE(events.pieceCaptured);
    EXPECT_FALSE(events.kingCaptured);
    EXPECT_FALSE(events.capturedPieceId.has_value());
}