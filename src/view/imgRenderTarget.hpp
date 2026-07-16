#pragma once

#include "imageCatalog.hpp"
#include "renderTarget.hpp"

class ImgRenderTarget : public RenderTarget
{
public:
    explicit ImgRenderTarget(
        ImageCatalog& imageCatalog
    );

    void beginFrame(
        int boardWidth,
        int boardHeight,
        int cellSize
    ) override;

    void drawPiece(
        const PieceSnapshot& piece
    ) override;

    void drawSelection(
        const Position& selectedCell,
        int cellSize
    ) override;

    void drawGameOver() override;

    void endFrame() override;

    int lastKey() const;

private:
    ImageCatalog& imageCatalog_;
    Img frame_;

    int boardWidth_;
    int boardHeight_;
    int cellSize_;
    int lastKey_;
};