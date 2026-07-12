#include <gtest/gtest.h>

#include "../../src/model/board.hpp"

TEST(BoardTest, StoresDimensions)
{
    const Board board(3, 4);

    EXPECT_EQ(board.width(), 3);
    EXPECT_EQ(board.height(), 4);
}

TEST(BoardTest, ReportsWhetherPositionIsInside)
{
    const Board board(3, 4);

    EXPECT_TRUE(board.isInside(Position(0, 0)));
    EXPECT_TRUE(board.isInside(Position(3, 2)));

    EXPECT_FALSE(board.isInside(Position(-1, 0)));
    EXPECT_FALSE(board.isInside(Position(4, 0)));
    EXPECT_FALSE(board.isInside(Position(0, 3)));
}

TEST(BoardTest, EmptyCellReturnsNull)
{
    const Board board(3, 3);

    EXPECT_EQ(
        board.getPieceAt(Position(1, 1)),
        nullptr
    );
}

TEST(BoardTest, CanAddAndFindPiece)
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

    const Piece* piece =
        board.getPieceAt(Position(1, 1));

    ASSERT_NE(piece, nullptr);
    EXPECT_EQ(piece->id(), 1);
    EXPECT_EQ(piece->kind(), PieceKind::Rook);
}

TEST(BoardTest, RejectsDuplicateOccupancy)
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

    EXPECT_THROW(
        board.addPiece(
            Piece(
                2,
                PieceColor::Black,
                PieceKind::Knight,
                Position(1, 1)
            )
        ),
        std::invalid_argument
    );
}

TEST(BoardTest, RejectsDuplicatePieceId)
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

    EXPECT_THROW(
        board.addPiece(
            Piece(
                1,
                PieceColor::Black,
                PieceKind::Knight,
                Position(2, 2)
            )
        ),
        std::invalid_argument
    );
}

TEST(BoardTest, MovesPiece)
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

    board.movePiece(
        Position(1, 1),
        Position(2, 1)
    );

    EXPECT_EQ(
        board.getPieceAt(Position(1, 1)),
        nullptr
    );

    const Piece* moved =
        board.getPieceAt(Position(2, 1));

    ASSERT_NE(moved, nullptr);
    EXPECT_EQ(moved->cell(), Position(2, 1));
}

TEST(BoardTest, RemovesPiece)
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

    board.removePiece(Position(1, 1));

    EXPECT_EQ(
        board.getPieceAt(Position(1, 1)),
        nullptr
    );
}