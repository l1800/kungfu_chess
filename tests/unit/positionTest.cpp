#include <gtest/gtest.h>

#include "../../src/model/position.hpp"

#include <sstream>

TEST(PositionTest, EqualPositionsAreEqual)
{
    const Position first(2, 3);
    const Position second(2, 3);

    EXPECT_EQ(first, second);
}

TEST(PositionTest, DifferentRowsAreNotEqual)
{
    const Position first(2, 3);
    const Position second(1, 3);

    EXPECT_NE(first, second);
}

TEST(PositionTest, DifferentColumnsAreNotEqual)
{
    const Position first(2, 3);
    const Position second(2, 4);

    EXPECT_NE(first, second);
}

TEST(PositionTest, ProducesReadableOutput)
{
    const Position position(2, 3);

    std::ostringstream output;
    output << position;

    EXPECT_EQ(
        output.str(),
        "Position(row=2, col=3)"
    );
}