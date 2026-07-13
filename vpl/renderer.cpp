#include "renderer.hpp"

Renderer::Renderer(RenderTarget& target)
    : target_(target)
{
}

void Renderer::draw(
    const GameSnapshot& snapshot
) const
{
    target_.beginFrame(
        snapshot.boardWidth,
        snapshot.boardHeight,
        snapshot.cellSize
    );

    for (const PieceSnapshot& piece :
        snapshot.pieces)
    {
        target_.drawPiece(piece);
    }

    if (snapshot.selectedCell.has_value())
    {
        target_.drawSelection(
            snapshot.selectedCell.value(),
            snapshot.cellSize
        );
    }

    if (snapshot.gameOver)
    {
        target_.drawGameOver();
    }

    target_.endFrame();
}