#include <gtest/gtest.h>

#include "../../src/io/boardParser.hpp"

#include <stdexcept>
#include <string>

TEST(BoardParserTest, ParsesRectangularBoard)
{
    const std::string input =
        ". . .\n"
        ". wK .\n"
        ". . .";

    const Board board = BoardParser::parse(input);

    EXPECT_EQ(board.width(), 3);
    EXPECT_EQ(board.height(), 3);

    const Piece* piece =
        board.getPieceAt(Position(1, 1));

    ASSERT_NE(piece, nullptr);
    EXPECT_EQ(piece->kind(), PieceKind::King);
    EXPECT_EQ(piece->color(), PieceColor::White);
    EXPECT_EQ(piece->cell(), Position(1, 1));
}

TEST(BoardParserTest, RejectsNonRectangularBoard)
{
    const std::string input =
        ". . .\n"
        ". wK\n"
        ". . .";

    EXPECT_THROW(
        BoardParser::parse(input),
        std::invalid_argument
    );
}

TEST(BoardParserTest, RejectsUnknownToken)
{
    const std::string input =
        ". . .\n"
        ". X .\n"
        ". . .";

    EXPECT_THROW(
        BoardParser::parse(input),
        std::invalid_argument
    );
}