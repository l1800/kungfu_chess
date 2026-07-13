#include <gtest/gtest.h>

#include "../../src/texttests/ScriptRunner.hpp"

#include <string>

TEST(
    ScriptRunnerTest,
    RookMovesOnlyAfterEnoughTime
)
{
    const std::string script =
        "Board\n"
        ". wR .\n"
        ". . .\n"
        ". . bK\n"
        "\n"
        "click 150 50\n"
        "click 150 250\n"
        "wait 1000\n"
        "print board\n"
        "wait 1000\n"
        "print board\n";

    const std::string expected =
        ". wR .\n"
        ". . .\n"
        ". . bK\n"
        "\n"
        ". . .\n"
        ". . .\n"
        ". wR bK";

    EXPECT_EQ(
        ScriptRunner::run(script),
        expected
    );
}