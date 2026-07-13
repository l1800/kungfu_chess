#include <gtest/gtest.h>

#include "../../src/rules/ruleEngine.hpp"

TEST(RuleEngineTest, RejectsOutsideBoard)
{
    const Board board(3, 3);
    const RuleEngine ruleEngine;

    const MoveValidation result =
        ruleEngine.validateMove(
            board,
            Position(0, 0),
            Position(3, 0)
        );

    EXPECT_FALSE(result.isValid);
    EXPECT_EQ(result.reason, "outside_board");
}

TEST(RuleEngineTest, RejectsEmptySource)
{
    const Board board(3, 3);
    const RuleEngine ruleEngine;

    const MoveValidation result =
        ruleEngine.validateMove(
            board,
            Position(0, 0),
            Position(0, 2)
        );

    EXPECT_FALSE(result.isValid);
    EXPECT_EQ(result.reason, "empty_source");
}

TEST(RuleEngineTest, RejectsFriendlyDestination)
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
            PieceColor::White,
            PieceKind::Pawn,
            Position(0, 2)
        )
    );

    const RuleEngine ruleEngine;

    const MoveValidation result =
        ruleEngine.validateMove(
            board,
            Position(0, 0),
            Position(0, 2)
        );

    EXPECT_FALSE(result.isValid);
    EXPECT_EQ(
        result.reason,
        "friendly_destination"
    );
}

TEST(RuleEngineTest, AcceptsLegalRookMove)
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

    const RuleEngine ruleEngine;

    const MoveValidation result =
        ruleEngine.validateMove(
            board,
            Position(0, 0),
            Position(0, 2)
        );

    EXPECT_TRUE(result.isValid);
    EXPECT_EQ(result.reason, "ok");
}

TEST(RuleEngineTest, RejectsDiagonalRookMove)
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

    const RuleEngine ruleEngine;

    const MoveValidation result =
        ruleEngine.validateMove(
            board,
            Position(0, 0),
            Position(1, 1)
        );

    EXPECT_FALSE(result.isValid);
    EXPECT_EQ(
        result.reason,
        "illegal_piece_move"
    );
}

TEST(RuleEngineTest, DoesNotChangeBoard)
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

    const RuleEngine ruleEngine;

    ruleEngine.validateMove(
        board,
        Position(0, 0),
        Position(0, 2)
    );

    EXPECT_NE(
        board.getPieceAt(Position(0, 0)),
        nullptr
    );

    EXPECT_EQ(
        board.getPieceAt(Position(0, 2)),
        nullptr
    );
}