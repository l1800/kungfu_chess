#pragma once

#include "../model/gameSnapshot.hpp"

class RenderTarget
{
public:
    virtual ~RenderTarget() = default;

    virtual void beginFrame(
        int boardWidth,
        int boardHeight,
        int cellSize
    ) = 0;

    virtual void drawPiece(
        const PieceSnapshot& piece
    ) = 0;

    virtual void drawSelection(
        const Position& selectedCell,
        int cellSize
    ) = 0;

    virtual void drawGameOver() = 0;

    virtual void endFrame() = 0;
};