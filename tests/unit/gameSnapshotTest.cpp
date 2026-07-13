#include <gtest/gtest.h>

#include "../../src/engine/gameEngine.hpp"

TEST(
    GameSnapshotTest,
    ContainsBoardDimensionsAndPieces
)
{
    Board board(3, 2);

    board.addPiece(
        Piece(
            1,
            PieceColor::White,
            PieceKind::Rook,
            Position(1, 2)
        )
    );

    RuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    GameEngine engine(
        board,
        ruleEngine,
        arbiter
    );

    const GameSnapshot snapshot =
        engine.snapshot();

    EXPECT_EQ(snapshot.boardWidth, 3);
    EXPECT_EQ(snapshot.boardHeight, 2);
    EXPECT_EQ(snapshot.cellSize, 100);
    EXPECT_FALSE(snapshot.gameOver);

    ASSERT_EQ(snapshot.pieces.size(), 1u);

    const PieceSnapshot& piece =
        snapshot.pieces.front();

    EXPECT_EQ(piece.id, 1);
    EXPECT_EQ(piece.color, PieceColor::White);
    EXPECT_EQ(piece.kind, PieceKind::Rook);
    EXPECT_EQ(piece.state, PieceState::Idle);

    EXPECT_DOUBLE_EQ(piece.pixelX, 200.0);
    EXPECT_DOUBLE_EQ(piece.pixelY, 100.0);
}

TEST(
    GameSnapshotTest,
    ContainsSelectedCellWithoutExposingController
)
{
    Board board(3, 3);
    RuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    GameEngine engine(
        board,
        ruleEngine,
        arbiter
    );

    const GameSnapshot snapshot =
        engine.snapshot(
            Position(1, 2)
        );

    ASSERT_TRUE(
        snapshot.selectedCell.has_value()
    );

    EXPECT_EQ(
        snapshot.selectedCell.value(),
        Position(1, 2)
    );
}

TEST(
    GameSnapshotTest,
    MovingPieceHasInterpolatedPixelPosition
)
{
    Board board(3, 1);

    board.addPiece(
        Piece(
            1,
            PieceColor::White,
            PieceKind::Rook,
            Position(0, 0)
        )
    );

    RuleEngine ruleEngine;
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

    engine.wait(1000);

    const GameSnapshot snapshot =
        engine.snapshot();

    ASSERT_EQ(snapshot.pieces.size(), 1u);

    const PieceSnapshot& piece =
        snapshot.pieces.front();

    EXPECT_EQ(piece.state, PieceState::Moving);
    EXPECT_DOUBLE_EQ(piece.pixelX, 100.0);
    EXPECT_DOUBLE_EQ(piece.pixelY, 0.0);

    /*
     * הלוח הלוגי עדיין לא השתנה.
     */
    EXPECT_NE(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    EXPECT_EQ(
        board.getPieceAt(Position(0, 2)),
        nullptr
    );
}

TEST(
    GameSnapshotTest,
    ContainsGameOverFlag
)
{
    Board board(2, 2);
    RuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    GameEngine engine(
        board,
        ruleEngine,
        arbiter
    );

    engine.setGameOver(true);

    const GameSnapshot snapshot =
        engine.snapshot();

    EXPECT_TRUE(snapshot.gameOver);
}