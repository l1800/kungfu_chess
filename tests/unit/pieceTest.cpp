#include <gtest/gtest.h>

#include "../../src/model/piece.hpp"

TEST(PieceTest, StoresInitialValues)
{
    const Piece piece(
        1,
        PieceColor::White,
        PieceKind::Knight,
        Position(2, 1)
    );

    EXPECT_EQ(piece.id(), 1);
    EXPECT_EQ(piece.color(), PieceColor::White);
    EXPECT_EQ(piece.kind(), PieceKind::Knight);
    EXPECT_EQ(piece.cell(), Position(2, 1));
    EXPECT_EQ(piece.state(), PieceState::Idle);
}