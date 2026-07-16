#include "imgRenderTarget.hpp"
#include <string>
#include <stdexcept>

ImgRenderTarget::ImgRenderTarget(
    ImageCatalog& imageCatalog
)
    : imageCatalog_(imageCatalog),
    boardWidth_(0),
    boardHeight_(0),
    cellSize_(0),
    lastKey_(-1)
{
}

void ImgRenderTarget::beginFrame(
    int boardWidth,
    int boardHeight,
    int cellSize
)
{
    if (boardWidth <= 0 ||
        boardHeight <= 0 ||
        cellSize <= 0)
    {
        throw std::invalid_argument(
            "Invalid frame dimensions."
        );
    }

    boardWidth_ = boardWidth;
    boardHeight_ = boardHeight;
    cellSize_ = cellSize;

    frame_.read(
        std::string(ASSETS_DIR) +
        "/board/chess_board.bmp",
        {
            boardWidth_ * cellSize_,
            boardHeight_ * cellSize_
        },
        false
    );
}

void ImgRenderTarget::drawPiece(
    const PieceSnapshot& piece
)
{
    Img& image =
        imageCatalog_.pieceImage(
            piece.color,
            piece.kind
        );

    image.draw_on(
        frame_,
        static_cast<int>(piece.pixelX),
        static_cast<int>(piece.pixelY)
    );
}

void ImgRenderTarget::drawSelection(
    const Position& selectedCell,
    int cellSize
)
{
    const int x =
        selectedCell.col() * cellSize;

    const int y =
        selectedCell.row() * cellSize;

    frame_.put_text(
        "X",
        x + 35,
        y + 65,
        1.5,
        cv::Scalar(0, 215, 255),
        3
    );
}

void ImgRenderTarget::drawGameOver()
{
    frame_.put_text(
        "GAME OVER",
        250,
        400,
        2.0,
        cv::Scalar(0, 215, 255),
        4
    );
}

void ImgRenderTarget::endFrame()
{
    lastKey_ = frame_.show_frame(
        "Kung Fu Chess",
        16
    );
}

int ImgRenderTarget::lastKey() const
{
    return lastKey_;
}