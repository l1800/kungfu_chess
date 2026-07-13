#include <gtest/gtest.h>

#include "../../src/texttests/ScriptRunner.hpp"

#include <string>

TEST(
    ScriptRunnerTest,
    KingCaptureEndsGameAndBlocksFurtherMoves
)
{
    const std::string script =
        "Board\n"
        "wR . bK\n"
        ". . wN\n"
        ". . .\n"
        "\n"
        "click 50 50\n"
        "click 250 50\n"
        "wait 2000\n"
        "print board\n"
        "click 250 150\n"
        "click 50 250\n"
        "wait 2000\n"
        "print board\n";

    const std::string expected =
        ". . wR\n"
        ". . wN\n"
        ". . .\n"
        "\n"
        ". . wR\n"
        ". . wN\n"
        ". . .";

    EXPECT_EQ(
        ScriptRunner::run(script),
        expected
    );
}
TEST(ScriptRunnerTest, BishopMovesDiagonally)
{
    const std::string script =
        "Board\n"
        ". . . .\n"
        ". . . .\n"
        ". . . .\n"
        "wB . . bK\n"
        "\n"
        "click 50 350\n"
        "click 350 50\n"
        "wait 3000\n"
        "print board\n";

    const std::string expected =
        ". . . wB\n"
        ". . . .\n"
        ". . . .\n"
        ". . . bK";

    EXPECT_EQ(
        ScriptRunner::run(script),
        expected
    );
}
TEST(ScriptRunnerTest, QueenMovesLikeBishop)
{
    const std::string script =
        "Board\n"
        ". . . .\n"
        ". . . .\n"
        ". wQ . .\n"
        ". . . bK\n"
        "\n"
        "click 150 250\n"
        "click 350 50\n"
        "wait 2000\n"
        "print board\n";

    const std::string expected =
        ". . . wQ\n"
        ". . . .\n"
        ". . . .\n"
        ". . . bK";

    EXPECT_EQ(
        ScriptRunner::run(script),
        expected
    );
}
TEST(ScriptRunnerTest, KnightMovesInLShape)
{
    const std::string script =
        "Board\n"
        ". . . .\n"
        ". . . .\n"
        ". wN . .\n"
        ". . . bK\n"
        "\n"
        "click 150 250\n"
        "click 250 50\n"
        "wait 2000\n"
        "print board\n";

    const std::string expected =
        ". . wN .\n"
        ". . . .\n"
        ". . . .\n"
        ". . . bK";

    EXPECT_EQ(
        ScriptRunner::run(script),
        expected
    );
}
TEST(ScriptRunnerTest, KingMovesOneSquare)
{
    const std::string script =
        "Board\n"
        ". . .\n"
        ". wK .\n"
        ". . bK\n"
        "\n"
        "click 150 150\n"
        "click 50 50\n"
        "wait 1000\n"
        "print board\n";

    const std::string expected =
        "wK . .\n"
        ". . .\n"
        ". . bK";

    EXPECT_EQ(
        ScriptRunner::run(script),
        expected
    );
}
TEST(ScriptRunnerTest, WhitePawnMovesOneSquareForward)
{
    const std::string script =
        "Board\n"
        ". . .\n"
        ". . .\n"
        ". wP .\n"
        ". . bK\n"
        "\n"
        "click 150 250\n"
        "click 150 150\n"
        "wait 1000\n"
        "print board\n";

    const std::string expected =
        ". . .\n"
        ". wP .\n"
        ". . .\n"
        ". . bK";

    EXPECT_EQ(
        ScriptRunner::run(script),
        expected
    );
}
TEST(
    ScriptRunnerTest,
    BlockedRookMoveLeavesBoardUnchanged
)
{
    const std::string script =
        "Board\n"
        "wR wP .\n"
        ". . .\n"
        ". . bK\n"
        "\n"
        "click 50 50\n"
        "click 250 50\n"
        "wait 3000\n"
        "print board\n";

    const std::string expected =
        "wR wP .\n"
        ". . .\n"
        ". . bK";

    EXPECT_EQ(
        ScriptRunner::run(script),
        expected
    );
}
TEST(
    ScriptRunnerTest,
    FriendlyDestinationLeavesBoardUnchanged
)
{
    const std::string script =
        "Board\n"
        "wR . wP\n"
        ". . .\n"
        ". . bK\n"
        "\n"
        "click 50 50\n"
        "click 250 50\n"
        "wait 2000\n"
        "print board\n";

    const std::string expected =
        "wR . wP\n"
        ". . .\n"
        ". . bK";

    EXPECT_EQ(
        ScriptRunner::run(script),
        expected
    );
}