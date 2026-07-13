#include <gtest/gtest.h>

#include "../../src/realtime/realTimeArbiter.hpp"

namespace
{
    void addWhiteRook(
        Board& board,
        const Position& position
    )
    {
        board.addPiece(
            Piece(
                1,
                PieceColor::White,
                PieceKind::Rook,
                position
            )
        );
    }
}

TEST(RealTimeArbiterTest, StartsActiveMotion)
{
    Board board(3, 3);
    addWhiteRook(board, Position(0, 0));

    RealTimeArbiter arbiter(board);

    arbiter.startMotion(
        Position(0, 0),
        Position(0, 1)
    );

    EXPECT_TRUE(arbiter.hasActiveMotion());

    const Piece* piece =
        board.getPieceAt(Position(0, 0));

    ASSERT_NE(piece, nullptr);
    EXPECT_EQ(piece->state(), PieceState::Moving);
}

TEST(
    RealTimeArbiterTest,
    BoardDoesNotChangeAfter999Milliseconds
)
{
    Board board(3, 3);
    addWhiteRook(board, Position(0, 0));

    RealTimeArbiter arbiter(board);

    arbiter.startMotion(
        Position(0, 0),
        Position(0, 1)
    );

    arbiter.advanceTime(999);

    EXPECT_NE(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    EXPECT_EQ(
        board.getPieceAt(Position(0, 1)),
        nullptr
    );

    EXPECT_TRUE(arbiter.hasActiveMotion());
}

TEST(
    RealTimeArbiterTest,
    OneCellMotionArrivesAfter1000Milliseconds
)
{
    Board board(3, 3);
    addWhiteRook(board, Position(0, 0));

    RealTimeArbiter arbiter(board);

    arbiter.startMotion(
        Position(0, 0),
        Position(0, 1)
    );

    arbiter.advanceTime(1000);

    EXPECT_EQ(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    const Piece* arrived =
        board.getPieceAt(Position(0, 1));

    ASSERT_NE(arrived, nullptr);
    EXPECT_EQ(arrived->state(), PieceState::Idle);

    EXPECT_FALSE(arbiter.hasActiveMotion());
}

TEST(
    RealTimeArbiterTest,
    MultiplePartialWaitsAccumulate
)
{
    Board board(3, 3);
    addWhiteRook(board, Position(0, 0));

    RealTimeArbiter arbiter(board);

    arbiter.startMotion(
        Position(0, 0),
        Position(0, 2)
    );

    arbiter.advanceTime(500);
    arbiter.advanceTime(500);

    EXPECT_NE(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    EXPECT_EQ(
        board.getPieceAt(Position(0, 2)),
        nullptr
    );

    arbiter.advanceTime(1000);

    EXPECT_EQ(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    EXPECT_NE(
        board.getPieceAt(Position(0, 2)),
        nullptr
    );
}

TEST(
    RealTimeArbiterTest,
    RejectsSecondDirectMotion
)
{
    Board board(3, 3);
    addWhiteRook(board, Position(0, 0));

    RealTimeArbiter arbiter(board);

    arbiter.startMotion(
        Position(0, 0),
        Position(0, 2)
    );

    EXPECT_THROW(
        arbiter.startMotion(
            Position(0, 0),
            Position(1, 0)
        ),
        std::logic_error
    );
}