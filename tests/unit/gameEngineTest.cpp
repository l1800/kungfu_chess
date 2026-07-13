#include <gtest/gtest.h>

#include "../../src/engine/gameEngine.hpp"

#include <optional>

class FakeRuleEngine : public RuleEngine
{
public:
    MoveValidation validateMove(
        const Board&,
        const Position& source,
        const Position& destination
    ) const override
    {
        called = true;
        receivedSource = source;
        receivedDestination = destination;

        return resultToReturn;
    }

    mutable bool called = false;

    mutable std::optional<Position>
        receivedSource;

    mutable std::optional<Position>
        receivedDestination;

    MoveValidation resultToReturn{
        true,
        "ok"
    };
};

TEST(
    GameEngineTest,
    RejectsGameOverBeforeValidation
)
{
    Board board(3, 3);
    FakeRuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    GameEngine engine(
        board,
        ruleEngine,
        arbiter
    );

    engine.setGameOver(true);

    const MoveResult result =
        engine.requestMove(
            Position(0, 0),
            Position(0, 1)
        );

    EXPECT_FALSE(result.isAccepted);
    EXPECT_EQ(result.reason, "game_over");
    EXPECT_FALSE(ruleEngine.called);
}

TEST(
    GameEngineTest,
    DelegatesLegalMoveToRuleEngine
)
{
    Board board(3, 3);

    board.addPiece(
        Piece(
            1,
            PieceColor::White,
            PieceKind::Rook,
            Position(0, 0)
        )
    );

    FakeRuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    GameEngine engine(
        board,
        ruleEngine,
        arbiter
    );

    const MoveResult result =
        engine.requestMove(
            Position(0, 0),
            Position(0, 1)
        );

    EXPECT_TRUE(ruleEngine.called);
    EXPECT_TRUE(result.isAccepted);
    EXPECT_EQ(result.reason, "ok");
    EXPECT_TRUE(arbiter.hasActiveMotion());
}

TEST(
    GameEngineTest,
    CopiesRuleEngineRejectionReason
)
{
    Board board(3, 3);
    FakeRuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    ruleEngine.resultToReturn = {
        false,
        "illegal_piece_move"
    };

    GameEngine engine(
        board,
        ruleEngine,
        arbiter
    );

    const MoveResult result =
        engine.requestMove(
            Position(0, 0),
            Position(1, 1)
        );

    EXPECT_FALSE(result.isAccepted);

    EXPECT_EQ(
        result.reason,
        "illegal_piece_move"
    );

    EXPECT_FALSE(arbiter.hasActiveMotion());
}

TEST(
    GameEngineTest,
    RejectsSecondMoveWhileMotionIsActive
)
{
    Board board(3, 3);

    board.addPiece(
        Piece(
            1,
            PieceColor::White,
            PieceKind::Rook,
            Position(0, 0)
        )
    );

    FakeRuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    GameEngine engine(
        board,
        ruleEngine,
        arbiter
    );

    const MoveResult first =
        engine.requestMove(
            Position(0, 0),
            Position(0, 2)
        );

    ASSERT_TRUE(first.isAccepted);

    ruleEngine.called = false;

    const MoveResult second =
        engine.requestMove(
            Position(0, 0),
            Position(1, 0)
        );

    EXPECT_FALSE(second.isAccepted);

    EXPECT_EQ(
        second.reason,
        "motion_in_progress"
    );

    /*
     * GameEngine דוחה לפני RuleEngine.
     */
    EXPECT_FALSE(ruleEngine.called);
}

TEST(
    GameEngineTest,
    WaitAdvancesMotionThroughArbiter
)
{
    Board board(3, 3);

    board.addPiece(
        Piece(
            1,
            PieceColor::White,
            PieceKind::Rook,
            Position(0, 0)
        )
    );

    FakeRuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    GameEngine engine(
        board,
        ruleEngine,
        arbiter
    );

    engine.requestMove(
        Position(0, 0),
        Position(0, 1)
    );

    engine.wait(999);

    EXPECT_NE(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    engine.wait(1);

    EXPECT_EQ(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    EXPECT_NE(
        board.getPieceAt(Position(0, 1)),
        nullptr
    );
}