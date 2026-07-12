#include <gtest/gtest.h>

#include "../../src/input/boardMapper.hpp"

TEST(BoardMapperTest, MapsTopLeftCell)
{
    const BoardMapper mapper(3, 3);

    const auto position = mapper.pixelToCell(50, 50);

    ASSERT_TRUE(position.has_value());
    EXPECT_EQ(position.value(), Position(0, 0));
}

TEST(BoardMapperTest, MapsSecondColumn)
{
    const BoardMapper mapper(3, 3);

    const auto position = mapper.pixelToCell(150, 50);

    ASSERT_TRUE(position.has_value());
    EXPECT_EQ(position.value(), Position(0, 1));
}

TEST(BoardMapperTest, MapsSecondRow)
{
    const BoardMapper mapper(3, 3);

    const auto position = mapper.pixelToCell(50, 150);

    ASSERT_TRUE(position.has_value());
    EXPECT_EQ(position.value(), Position(1, 0));
}

TEST(BoardMapperTest, MapsCellBoundaries)
{
    const BoardMapper mapper(3, 3);

    EXPECT_EQ(
        mapper.pixelToCell(0, 0).value(),
        Position(0, 0)
    );

    EXPECT_EQ(
        mapper.pixelToCell(99, 99).value(),
        Position(0, 0)
    );

    EXPECT_EQ(
        mapper.pixelToCell(100, 100).value(),
        Position(1, 1)
    );
}

TEST(BoardMapperTest, RejectsNegativeCoordinates)
{
    const BoardMapper mapper(3, 3);

    EXPECT_FALSE(mapper.pixelToCell(-1, 50).has_value());
    EXPECT_FALSE(mapper.pixelToCell(50, -1).has_value());
}

TEST(BoardMapperTest, RejectsCoordinatesOutsideBoard)
{
    const BoardMapper mapper(3, 3);

    EXPECT_FALSE(mapper.pixelToCell(300, 50).has_value());
    EXPECT_FALSE(mapper.pixelToCell(50, 300).has_value());
}