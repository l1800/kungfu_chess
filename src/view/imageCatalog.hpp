#pragma once

#include "../graphics/img.hpp"
#include "../model/piece.hpp"

class ImageCatalog
{
public:
    explicit ImageCatalog(int cellSize);

    Img& pieceImage(
        PieceColor color,
        PieceKind kind
    );

private:
    void loadImages();

    int cellSize_;

    Img whiteKing_;
    Img whiteQueen_;
    Img whiteRook_;
    Img whiteBishop_;
    Img whiteKnight_;
    Img whitePawn_;

    Img blackKing_;
    Img blackQueen_;
    Img blackRook_;
    Img blackBishop_;
    Img blackKnight_;
    Img blackPawn_;
};