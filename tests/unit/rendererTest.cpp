#include <gtest/gtest.h>

#include "../../src/view/renderer.hpp"

#include <vector>

class FakeRenderTarget : public RenderTarget
{
public:
    void beginFrame(
        int boardWidth,
        int boardHeight,
        int cellSize
    ) override
    {
        beginCalled = true;
        receivedWidth = boardWidth;
        receivedHeight = boardHeight;
        receivedCellSize = cellSize;
    }

    void drawPiece(
        const PieceSnapshot& piece
    ) override
    {
        drawnPieces.push_back(piece);
    }

    void drawSelection(
        const Position& selectedCell,
        int cellSize
    ) override
    {
        selectionCalled = true;
        receivedSelection = selectedCell;
        receivedCellSize = cellSize;
    }

    void drawGameOver() override
    {
        gameOverCalled = true;
    }

    void endFrame() override
    {
        endCalled = true;
    }

    bool beginCalled = false;
    bool endCalled = false;
    bool selectionCalled = false;
    bool gameOverCalled = false;

    int receivedWidth = 0;
    int receivedHeight = 0;
    int receivedCellSize = 0;

    std::optional<Position> receivedSelection;
    std::vector<PieceSnapshot> drawnPieces;
};

TEST(
    RendererTest,
    DrawsSnapshotWithoutChangingIt
)
{
    GameSnapshot snapshot{
        3,
        2,
        100,
        {
            {
                1,
                PieceColor::White,
                PieceKind::Rook,
                PieceState::Idle,
                100.0,
                0.0
            }
        },
        Position(0, 1),
        true
    };

    const GameSnapshot original = snapshot;

    FakeRenderTarget target;
    Renderer renderer(target);

    renderer.draw(snapshot);

    EXPECT_TRUE(target.beginCalled);
    EXPECT_TRUE(target.endCalled);

    EXPECT_EQ(target.receivedWidth, 3);
    EXPECT_EQ(target.receivedHeight, 2);
    EXPECT_EQ(target.receivedCellSize, 100);

    ASSERT_EQ(target.drawnPieces.size(), 1u);
    EXPECT_EQ(target.drawnPieces.front().id, 1);

    EXPECT_TRUE(target.selectionCalled);
    EXPECT_TRUE(target.gameOverCalled);

    /*
     * Smoke test: הרינדור לא שינה את המידע.
     */
    EXPECT_EQ(snapshot.boardWidth, original.boardWidth);
    EXPECT_EQ(snapshot.boardHeight, original.boardHeight);
    EXPECT_EQ(snapshot.pieces.size(), original.pieces.size());
    EXPECT_EQ(snapshot.gameOver, original.gameOver);
}

TEST(
    RendererTest,
    DoesNotDrawOptionalElementsWhenAbsent
)
{
    const GameSnapshot snapshot{
        3,
        3,
        100,
        {},
        std::nullopt,
        false
    };

    FakeRenderTarget target;
    Renderer renderer(target);

    renderer.draw(snapshot);

    EXPECT_TRUE(target.beginCalled);
    EXPECT_TRUE(target.endCalled);

    EXPECT_FALSE(target.selectionCalled);
    EXPECT_FALSE(target.gameOverCalled);
    EXPECT_TRUE(target.drawnPieces.empty());
}