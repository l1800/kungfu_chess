#include <gtest/gtest.h>

#include "../../src/rules/rookRule.hpp"

TEST(RookRuleTest, MovesAlongRowsAndColumns)
{
    Board board(3, 3);

    board.addPiece(
        Piece(
            1,
            PieceColor::White,
            PieceKind::Rook,
            Position(1, 1)
        )
    );

    const Piece* rook =
        board.getPieceAt(Position(1, 1));

    ASSERT_NE(rook, nullptr);

    const std::set<Position> destinations =
        RookRule::legalDestinations(
            board,
            *rook
        );

    const std::set<Position> expected = {
        Position(0, 1),
        Position(2, 1),
        Position(1, 0),
        Position(1, 2)
    };

    EXPECT_EQ(destinations, expected);
}

TEST(RookRuleTest, DoesNotMoveDiagonally)
{
    Board board(3, 3);

    board.addPiece(
        Piece(
            1,
            PieceColor::White,
            PieceKind::Rook,
            Position(1, 1)
        )
    );

    const Piece* rook =
        board.getPieceAt(Position(1, 1));

    ASSERT_NE(rook, nullptr);

    const std::set<Position> destinations =
        RookRule::legalDestinations(
            board,
            *rook
        );

    EXPECT_EQ(
        destinations.count(Position(0, 0)),
        0u
    );

    EXPECT_EQ(
        destinations.count(Position(0, 2)),
        0u
    );

    EXPECT_EQ(
        destinations.count(Position(2, 0)),
        0u
    );

    EXPECT_EQ(
        destinations.count(Position(2, 2)),
        0u
    );
}

TEST(RookRuleTest, StopsBeforeFriendlyPiece)
{
    Board board(5, 1);

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

    const Piece* rook =
        board.getPieceAt(Position(0, 0));

    ASSERT_NE(rook, nullptr);

    const std::set<Position> destinations =
        RookRule::legalDestinations(
            board,
            *rook
        );

    EXPECT_EQ(
        destinations.count(Position(0, 1)),
        1u
    );

    EXPECT_EQ(
        destinations.count(Position(0, 2)),
        0u
    );

    EXPECT_EQ(
        destinations.count(Position(0, 3)),
        0u
    );

    EXPECT_EQ(
        destinations.count(Position(0, 4)),
        0u
    );
}

TEST(RookRuleTest, IncludesEnemyPieceAsDestination)
{
    Board board(5, 1);

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
            Position(0, 2)
        )
    );

    const Piece* rook =
        board.getPieceAt(Position(0, 0));

    ASSERT_NE(rook, nullptr);

    const std::set<Position> destinations =
        RookRule::legalDestinations(
            board,
            *rook
        );

    EXPECT_EQ(
        destinations.count(Position(0, 1)),
        1u
    );

    EXPECT_EQ(
        destinations.count(Position(0, 2)),
        1u
    );
}

TEST(RookRuleTest, CannotMovePastEnemyPiece)
{
    Board board(5, 1);

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
            Position(0, 2)
        )
    );

    const Piece* rook =
        board.getPieceAt(Position(0, 0));

    ASSERT_NE(rook, nullptr);

    const std::set<Position> destinations =
        RookRule::legalDestinations(
            board,
            *rook
        );

    EXPECT_EQ(
        destinations.count(Position(0, 3)),
        0u
    );

    EXPECT_EQ(
        destinations.count(Position(0, 4)),
        0u
    );
}

TEST(RookRuleTest, RejectsNonRookPiece)
{
    Board board(3, 3);

    board.addPiece(
        Piece(
            1,
            PieceColor::White,
            PieceKind::Bishop,
            Position(1, 1)
        )
    );

    const Piece* bishop =
        board.getPieceAt(Position(1, 1));

    ASSERT_NE(bishop, nullptr);

    EXPECT_THROW(
        RookRule::legalDestinations(
            board,
            *bishop
        ),
        std::invalid_argument
    );
}