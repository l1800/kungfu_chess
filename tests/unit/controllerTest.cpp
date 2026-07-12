#include <gtest/gtest.h>

#include "../../src/input/controller.hpp"

#include <optional>

class FakeMoveRequester : public MoveRequester
{
public:
    void requestMove(
        const Position& source,
        const Position& destination
    ) override
    {
        called = true;
        receivedSource = source;
        receivedDestination = destination;
    }

    bool called = false;
    std::optional<Position> receivedSource;
    std::optional<Position> receivedDestination;
};

TEST(ControllerTest, FirstClickOnPieceSelectsIt)
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

    const BoardMapper mapper(3, 3);
    FakeMoveRequester requester;

    Controller controller(board, mapper, requester);

    controller.click(150, 150);

    ASSERT_TRUE(controller.selectedCell().has_value());
    EXPECT_EQ(
        controller.selectedCell().value(),
        Position(1, 1)
    );

    EXPECT_FALSE(requester.called);
}

TEST(ControllerTest, FirstClickOnEmptyCellIsIgnored)
{
    const Board board(3, 3);
    const BoardMapper mapper(3, 3);
    FakeMoveRequester requester;

    Controller controller(board, mapper, requester);

    controller.click(50, 50);

    EXPECT_FALSE(controller.selectedCell().has_value());
    EXPECT_FALSE(requester.called);
}

TEST(ControllerTest, OutsideClickWithoutSelectionIsIgnored)
{
    const Board board(3, 3);
    const BoardMapper mapper(3, 3);
    FakeMoveRequester requester;

    Controller controller(board, mapper, requester);

    controller.click(350, 50);

    EXPECT_FALSE(controller.selectedCell().has_value());
    EXPECT_FALSE(requester.called);
}

TEST(ControllerTest, SecondInsideClickRequestsMove)
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

    const BoardMapper mapper(3, 3);
    FakeMoveRequester requester;

    Controller controller(board, mapper, requester);

    controller.click(50, 50);
    controller.click(250, 150);

    EXPECT_TRUE(requester.called);

    ASSERT_TRUE(requester.receivedSource.has_value());
    ASSERT_TRUE(requester.receivedDestination.has_value());

    EXPECT_EQ(
        requester.receivedSource.value(),
        Position(0, 0)
    );

    EXPECT_EQ(
        requester.receivedDestination.value(),
        Position(1, 2)
    );

    EXPECT_FALSE(controller.selectedCell().has_value());
}

TEST(ControllerTest, OutsideClickWithSelectionCancelsSelection)
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

    const BoardMapper mapper(3, 3);
    FakeMoveRequester requester;

    Controller controller(board, mapper, requester);

    controller.click(50, 50);

    ASSERT_TRUE(controller.selectedCell().has_value());

    controller.click(350, 50);

    EXPECT_FALSE(controller.selectedCell().has_value());
    EXPECT_FALSE(requester.called);
}