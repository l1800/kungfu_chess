#include <gtest/gtest.h>

#include "../../src/input/controller.hpp"

#include <optional>
class FakeGameEngine : public GameEngine
{
public:
    FakeGameEngine(
        Board& board,
        RuleEngine& ruleEngine,
        RealTimeArbiter& arbiter
    )
        : GameEngine(
            board,
            ruleEngine,
            arbiter
        )
    {
    }

    MoveResult requestMove(
        const Position& source,
        const Position& destination
    ) override
    {
        called = true;
        receivedSource = source;
        receivedDestination = destination;

        return resultToReturn;
    }

    bool called = false;

    std::optional<Position>
        receivedSource;

    std::optional<Position>
        receivedDestination;

    MoveResult resultToReturn{
        true,
        "ok"
    };
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

    RuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    FakeGameEngine gameEngine(
        board,
        ruleEngine,
        arbiter
    );
    BoardMapper mapper(3, 3);

    Controller controller(
        board,
        mapper,
        gameEngine
    );

    controller.click(150, 150);

    ASSERT_TRUE(controller.selectedCell().has_value());

    EXPECT_EQ(
        controller.selectedCell().value(),
        Position(1, 1)
    );

    EXPECT_FALSE(gameEngine.called);
}

TEST(ControllerTest, FirstClickOnEmptyCellIsIgnored)
{
    Board board(3, 3);
    RuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    FakeGameEngine gameEngine(
        board,
        ruleEngine,
        arbiter
    );
    BoardMapper mapper(3, 3);

    Controller controller(
        board,
        mapper,
        gameEngine
    );

    controller.click(50, 50);

    EXPECT_FALSE(controller.selectedCell().has_value());
    EXPECT_FALSE(gameEngine.called);
}

TEST(ControllerTest, OutsideClickWithoutSelectionIsIgnored)
{
    Board board(3, 3);
    RuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    FakeGameEngine gameEngine(
        board,
        ruleEngine,
        arbiter
    );
    BoardMapper mapper(3, 3);

    Controller controller(
        board,
        mapper,
        gameEngine
    );

    controller.click(350, 50);

    EXPECT_FALSE(controller.selectedCell().has_value());
    EXPECT_FALSE(gameEngine.called);
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

    RuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    FakeGameEngine gameEngine(
        board,
        ruleEngine,
        arbiter
    );
    BoardMapper mapper(3, 3);

    Controller controller(
        board,
        mapper,
        gameEngine
    );

    controller.click(50, 50);
    controller.click(250, 150);

    EXPECT_TRUE(gameEngine.called);

    ASSERT_TRUE(gameEngine.receivedSource.has_value());
    ASSERT_TRUE(gameEngine.receivedDestination.has_value());

    EXPECT_EQ(
        gameEngine.receivedSource.value(),
        Position(0, 0)
    );

    EXPECT_EQ(
        gameEngine.receivedDestination.value(),
        Position(1, 2)
    );

    EXPECT_FALSE(controller.selectedCell().has_value());
}

TEST(ControllerTest, RejectedMoveStillClearsSelection)
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

    RuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    FakeGameEngine gameEngine(
        board,
        ruleEngine,
        arbiter
    );

    gameEngine.resultToReturn = {
        false,
        "illegal_piece_move"
    };

    BoardMapper mapper(3, 3);

    Controller controller(
        board,
        mapper,
        gameEngine
    );

    controller.click(50, 50);
    controller.click(150, 150);

    EXPECT_TRUE(gameEngine.called);
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

    RuleEngine ruleEngine;
    RealTimeArbiter arbiter(board);

    FakeGameEngine gameEngine(
        board,
        ruleEngine,
        arbiter
    );
    BoardMapper mapper(3, 3);

    Controller controller(
        board,
        mapper,
        gameEngine
    );

    controller.click(50, 50);

    ASSERT_TRUE(controller.selectedCell().has_value());

    controller.click(350, 50);

    EXPECT_FALSE(controller.selectedCell().has_value());
    EXPECT_FALSE(gameEngine.called);
}