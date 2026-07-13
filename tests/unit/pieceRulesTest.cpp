#include <gtest/gtest.h>

#include "../../src/rules/pieceRules.hpp"

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

    const Piece& requirePiece(
        const Board& board,
        const Position& position
    )
    {
        const Piece* piece =
            board.getPieceAt(position);

        if (piece == nullptr)
        {
            throw std::logic_error(
                "test_piece_missing"
            );
        }

        return *piece;
    }
}

/* =========================
   Rook
   ========================= */

TEST(PieceRulesTest, RookMovesHorizontallyAndVertically)
{
    Board board(3, 3);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Rook,
        Position(1, 1)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(1, 1))
        );

    const std::set<Position> expected = {
        Position(0, 1),
        Position(2, 1),
        Position(1, 0),
        Position(1, 2)
    };

    EXPECT_EQ(destinations, expected);
}

TEST(PieceRulesTest, RookStopsBeforeFriendlyBlocker)
{
    Board board(5, 1);

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
        PieceColor::White,
        PieceKind::Pawn,
        Position(0, 2)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(0, 0))
        );

    EXPECT_EQ(destinations.count(Position(0, 1)), 1u);
    EXPECT_EQ(destinations.count(Position(0, 2)), 0u);
    EXPECT_EQ(destinations.count(Position(0, 3)), 0u);
}

TEST(PieceRulesTest, RookIncludesEnemyButNotSquaresBeyond)
{
    Board board(5, 1);

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
        Position(0, 2)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(0, 0))
        );

    EXPECT_EQ(destinations.count(Position(0, 1)), 1u);
    EXPECT_EQ(destinations.count(Position(0, 2)), 1u);
    EXPECT_EQ(destinations.count(Position(0, 3)), 0u);
}

/* =========================
   Bishop
   ========================= */

TEST(PieceRulesTest, BishopMovesOnlyDiagonally)
{
    Board board(5, 5);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Bishop,
        Position(2, 2)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(2, 2))
        );

    EXPECT_EQ(destinations.count(Position(0, 0)), 1u);
    EXPECT_EQ(destinations.count(Position(0, 4)), 1u);
    EXPECT_EQ(destinations.count(Position(4, 0)), 1u);
    EXPECT_EQ(destinations.count(Position(4, 4)), 1u);

    EXPECT_EQ(destinations.count(Position(2, 0)), 0u);
    EXPECT_EQ(destinations.count(Position(0, 2)), 0u);
}

TEST(PieceRulesTest, BishopStopsAtFriendlyBlocker)
{
    Board board(5, 5);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Bishop,
        Position(0, 0)
    );

    addPiece(
        board,
        2,
        PieceColor::White,
        PieceKind::Pawn,
        Position(2, 2)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(0, 0))
        );

    EXPECT_EQ(destinations.count(Position(1, 1)), 1u);
    EXPECT_EQ(destinations.count(Position(2, 2)), 0u);
    EXPECT_EQ(destinations.count(Position(3, 3)), 0u);
}

TEST(PieceRulesTest, BishopCanCaptureEnemyButCannotPassIt)
{
    Board board(5, 5);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Bishop,
        Position(0, 0)
    );

    addPiece(
        board,
        2,
        PieceColor::Black,
        PieceKind::Knight,
        Position(2, 2)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(0, 0))
        );

    EXPECT_EQ(destinations.count(Position(1, 1)), 1u);
    EXPECT_EQ(destinations.count(Position(2, 2)), 1u);
    EXPECT_EQ(destinations.count(Position(3, 3)), 0u);
}

/* =========================
   Queen
   ========================= */

TEST(PieceRulesTest, QueenCombinesRookAndBishopMoves)
{
    Board board(5, 5);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Queen,
        Position(2, 2)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(2, 2))
        );

    EXPECT_EQ(destinations.count(Position(2, 0)), 1u);
    EXPECT_EQ(destinations.count(Position(0, 2)), 1u);
    EXPECT_EQ(destinations.count(Position(0, 0)), 1u);
    EXPECT_EQ(destinations.count(Position(4, 4)), 1u);
}

/* =========================
   Knight
   ========================= */

TEST(PieceRulesTest, KnightMovesInLShape)
{
    Board board(5, 5);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Knight,
        Position(2, 2)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(2, 2))
        );

    EXPECT_EQ(destinations.size(), 8u);
    EXPECT_EQ(destinations.count(Position(0, 1)), 1u);
    EXPECT_EQ(destinations.count(Position(0, 3)), 1u);
    EXPECT_EQ(destinations.count(Position(4, 1)), 1u);
    EXPECT_EQ(destinations.count(Position(4, 3)), 1u);
}

TEST(PieceRulesTest, KnightJumpsOverBlockers)
{
    Board board(5, 5);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Knight,
        Position(2, 2)
    );

    int id = 2;

    for (int row = 1; row <= 3; ++row)
    {
        for (int col = 1; col <= 3; ++col)
        {
            if (row == 2 && col == 2)
            {
                continue;
            }

            addPiece(
                board,
                id++,
                PieceColor::White,
                PieceKind::Pawn,
                Position(row, col)
            );
        }
    }

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(2, 2))
        );

    EXPECT_EQ(destinations.count(Position(0, 1)), 1u);
    EXPECT_EQ(destinations.count(Position(1, 4)), 1u);
}

TEST(PieceRulesTest, KnightCannotLandOnFriendlyPiece)
{
    Board board(5, 5);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Knight,
        Position(2, 2)
    );

    addPiece(
        board,
        2,
        PieceColor::White,
        PieceKind::Pawn,
        Position(0, 1)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(2, 2))
        );

    EXPECT_EQ(destinations.count(Position(0, 1)), 0u);
}

/* =========================
   King
   ========================= */

TEST(PieceRulesTest, KingMovesOneSquareInEveryDirection)
{
    Board board(3, 3);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::King,
        Position(1, 1)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(1, 1))
        );

    EXPECT_EQ(destinations.size(), 8u);
    EXPECT_EQ(destinations.count(Position(0, 0)), 1u);
    EXPECT_EQ(destinations.count(Position(0, 1)), 1u);
    EXPECT_EQ(destinations.count(Position(2, 2)), 1u);
}

TEST(PieceRulesTest, KingCannotMoveTwoSquares)
{
    Board board(5, 5);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::King,
        Position(2, 2)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(2, 2))
        );

    EXPECT_EQ(destinations.count(Position(0, 2)), 0u);
    EXPECT_EQ(destinations.count(Position(2, 4)), 0u);
}

/* =========================
   Pawn
   ========================= */

TEST(PieceRulesTest, WhitePawnMovesOneRowUp)
{
    Board board(3, 4);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Pawn,
        Position(2, 1)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(2, 1))
        );

    EXPECT_EQ(destinations.count(Position(1, 1)), 1u);
    EXPECT_EQ(destinations.count(Position(0, 1)), 0u);
}

TEST(PieceRulesTest, BlackPawnMovesOneRowDown)
{
    Board board(3, 4);

    addPiece(
        board,
        1,
        PieceColor::Black,
        PieceKind::Pawn,
        Position(1, 1)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(1, 1))
        );

    EXPECT_EQ(destinations.count(Position(2, 1)), 1u);
    EXPECT_EQ(destinations.count(Position(3, 1)), 0u);
}

TEST(PieceRulesTest, PawnCannotMoveForwardIntoOccupiedCell)
{
    Board board(3, 4);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Pawn,
        Position(2, 1)
    );

    addPiece(
        board,
        2,
        PieceColor::Black,
        PieceKind::Knight,
        Position(1, 1)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(2, 1))
        );

    EXPECT_EQ(destinations.count(Position(1, 1)), 0u);
}

TEST(PieceRulesTest, PawnCapturesEnemyDiagonally)
{
    Board board(3, 4);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Pawn,
        Position(2, 1)
    );

    addPiece(
        board,
        2,
        PieceColor::Black,
        PieceKind::Knight,
        Position(1, 0)
    );

    addPiece(
        board,
        3,
        PieceColor::Black,
        PieceKind::Bishop,
        Position(1, 2)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(2, 1))
        );

    EXPECT_EQ(destinations.count(Position(1, 0)), 1u);
    EXPECT_EQ(destinations.count(Position(1, 2)), 1u);
}

TEST(PieceRulesTest, PawnCannotMoveDiagonallyToEmptyCell)
{
    Board board(3, 4);

    addPiece(
        board,
        1,
        PieceColor::White,
        PieceKind::Pawn,
        Position(2, 1)
    );

    const auto destinations =
        PieceRules::legalDestinations(
            board,
            requirePiece(board, Position(2, 1))
        );

    EXPECT_EQ(destinations.count(Position(1, 0)), 0u);
    EXPECT_EQ(destinations.count(Position(1, 2)), 0u);
}