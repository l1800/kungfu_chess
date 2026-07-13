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
    CapturingKingSetsGameOver
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

    board.addPiece(
        Piece(
            2,
            PieceColor::Black,
            PieceKind::King,
            Position(0, 2)
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
            Position(0, 2)
        );

    ASSERT_TRUE(result.isAccepted);
    EXPECT_FALSE(engine.isGameOver());

    engine.wait(1999);

    EXPECT_FALSE(engine.isGameOver());

    engine.wait(1);

    EXPECT_TRUE(engine.isGameOver());
}

TEST(
    GameEngineTest,
    RejectsMoveAfterKingCapture
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

    board.addPiece(
        Piece(
            2,
            PieceColor::Black,
            PieceKind::King,
            Position(0, 2)
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
        Position(0, 2)
    );

    engine.wait(2000);

    ASSERT_TRUE(engine.isGameOver());

    ruleEngine.called = false;

    const MoveResult result =
        engine.requestMove(
            Position(0, 2),
            Position(1, 2)
        );

    EXPECT_FALSE(result.isAccepted);
    EXPECT_EQ(result.reason, "game_over");

    /*
     * GameEngine דוחה לפני RuleEngine.
     */
    EXPECT_FALSE(ruleEngine.called);
}

TEST(
    GameEngineTest,
    NonKingCaptureDoesNotEndGame
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

    board.addPiece(
        Piece(
            2,
            PieceColor::Black,
            PieceKind::Knight,
            Position(0, 1)
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

    engine.wait(1000);

    EXPECT_FALSE(engine.isGameOver());

    const Piece* arrived =
        board.getPieceAt(Position(0, 1));

    ASSERT_NE(arrived, nullptr);
    EXPECT_EQ(arrived->id(), 1);
}