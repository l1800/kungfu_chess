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

    mutable std::optional<Position> receivedSource;
    mutable std::optional<Position> receivedDestination;

    MoveValidation resultToReturn{ true, "ok" };
};

TEST(GameEngineTest, RejectsGameOverBeforeValidation)
{
    Board board(3, 3);
    FakeRuleEngine ruleEngine;

    GameEngine engine(board, ruleEngine);
    engine.setGameOver(true);

    const MoveResult result =
        engine.requestMove(
            Position(0, 0),
            Position(0, 2)
        );

    EXPECT_FALSE(result.isAccepted);
    EXPECT_EQ(result.reason, "game_over");
    EXPECT_FALSE(ruleEngine.called);
}

TEST(GameEngineTest, DelegatesRequestToRuleEngine)
{
    Board board(3, 3);
    FakeRuleEngine ruleEngine;

    GameEngine engine(board, ruleEngine);

    const MoveResult result =
        engine.requestMove(
            Position(0, 0),
            Position(0, 2)
        );

    EXPECT_TRUE(ruleEngine.called);

    ASSERT_TRUE(
        ruleEngine.receivedSource.has_value()
    );

    ASSERT_TRUE(
        ruleEngine.receivedDestination.has_value()
    );

    EXPECT_EQ(
        ruleEngine.receivedSource.value(),
        Position(0, 0)
    );

    EXPECT_EQ(
        ruleEngine.receivedDestination.value(),
        Position(0, 2)
    );

    EXPECT_TRUE(result.isAccepted);
    EXPECT_EQ(result.reason, "ok");
}

TEST(GameEngineTest, CopiesRuleEngineRejectionReason)
{
    Board board(3, 3);
    FakeRuleEngine ruleEngine;

    ruleEngine.resultToReturn = {
        false,
        "illegal_piece_move"
    };

    GameEngine engine(board, ruleEngine);

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
}

TEST(GameEngineTest, AcceptedMoveDoesNotChangeBoard)
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
    GameEngine engine(board, ruleEngine);

    const MoveResult result =
        engine.requestMove(
            Position(0, 0),
            Position(0, 2)
        );

    EXPECT_TRUE(result.isAccepted);

    EXPECT_NE(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    EXPECT_EQ(
        board.getPieceAt(Position(0, 2)),
        nullptr
    );
}