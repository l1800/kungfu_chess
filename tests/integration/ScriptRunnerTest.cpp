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