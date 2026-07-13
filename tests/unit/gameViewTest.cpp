#include <gtest/gtest.h>

#include "../../src/view/gameView.hpp"

class NullRenderTarget : public RenderTarget
{
public:
    void beginFrame(
        int,
        int,
        int
    ) override
    {
    }

    void drawPiece(
        const PieceSnapshot&
    ) override
    {
    }

    void drawSelection(
        const Position&,
        int
    ) override
    {
    }

    void drawGameOver() override
    {
    }

    void endFrame() override
    {
    }
};

TEST(
    GameViewTest,
    ClickIsRoutedThroughController
)
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

    GameEngine engine(
        board,
        ruleEngine,
        arbiter
    );

    BoardMapper mapper(3, 3);

    Controller controller(
        board,
        mapper,
        engine
    );

    NullRenderTarget target;
    Renderer renderer(target);

    GameView view(
        controller,
        engine,
        renderer
    );

    view.onClick(50, 50);

    ASSERT_TRUE(
        controller.selectedCell().has_value()
    );

    EXPECT_EQ(
        controller.selectedCell().value(),
        Position(0, 0)
    );
}