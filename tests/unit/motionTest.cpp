#include <gtest/gtest.h>

#include "../../src/realtime/motion.hpp"

TEST(MotionTest, OneCellTakes1000Milliseconds)
{
    Motion motion(
        1,
        Position(0, 0),
        Position(0, 1)
    );

    EXPECT_EQ(motion.durationMs(), 1000);
}

TEST(MotionTest, TwoCellsTake2000Milliseconds)
{
    Motion motion(
        1,
        Position(0, 0),
        Position(0, 2)
    );

    EXPECT_EQ(motion.durationMs(), 2000);
}

TEST(MotionTest, DiagonalDurationUsesCellSteps)
{
    Motion motion(
        1,
        Position(0, 0),
        Position(3, 3)
    );

    EXPECT_EQ(motion.durationMs(), 3000);
}

TEST(MotionTest, PartialAdvancesAccumulate)
{
    Motion motion(
        1,
        Position(0, 0),
        Position(0, 2)
    );

    motion.advance(400);
    motion.advance(600);

    EXPECT_EQ(motion.elapsedMs(), 1000);
    EXPECT_FALSE(motion.isComplete());
}

TEST(MotionTest, CompletesAtRequiredDuration)
{
    Motion motion(
        1,
        Position(0, 0),
        Position(0, 1)
    );

    motion.advance(1000);

    EXPECT_TRUE(motion.isComplete());
}

TEST(MotionTest, RejectsNegativeTime)
{
    Motion motion(
        1,
        Position(0, 0),
        Position(0, 1)
    );

    EXPECT_THROW(
        motion.advance(-1),
        std::invalid_argument
    );
}