#include "imageCatalog.hpp"

#include <stdexcept>
#include <utility>

ImageCatalog::ImageCatalog(int cellSize)
    : cellSize_(cellSize)
{
    if (cellSize_ <= 0)
    {
        throw std::invalid_argument(
            "Cell size must be positive."
        );
    }

    loadImages();
}

void ImageCatalog::loadImages()
{
    const std::pair<int, int> size{
        cellSize_,
        cellSize_
    };

    whiteKing_.read(
        "assets/pieces/wK.png",
        size,
        true
    );

    whiteQueen_.read(
        "assets/pieces/wQ.png",
        size,
        true
    );

    whiteRook_.read(
        "assets/pieces/wR.png",
        size,
        true
    );

    whiteBishop_.read(
        "assets/pieces/wB.png",
        size,
        true
    );

    whiteKnight_.read(
        "assets/pieces/wN.png",
        size,
        true
    );

    whitePawn_.read(
        "assets/pieces/wP.png",
        size,
        true
    );

    blackKing_.read(
        "assets/pieces/bK.png",
        size,
        true
    );

    blackQueen_.read(
        "assets/pieces/bQ.png",
        size,
        true
    );

    blackRook_.read(
        "assets/pieces/bR.png",
        size,
        true
    );

    blackBishop_.read(
        "assets/pieces/bB.png",
        size,
        true
    );

    blackKnight_.read(
        "assets/pieces/bN.png",
        size,
        true
    );

    blackPawn_.read(
        "assets/pieces/bP.png",
        size,
        true
    );
}

Img& ImageCatalog::pieceImage(
    PieceColor color,
    PieceKind kind
)
{
    if (color == PieceColor::White)
    {
        switch (kind)
        {
        case PieceKind::King:
            return whiteKing_;

        case PieceKind::Queen:
            return whiteQueen_;

        case PieceKind::Rook:
            return whiteRook_;

        case PieceKind::Bishop:
            return whiteBishop_;

        case PieceKind::Knight:
            return whiteKnight_;

        case PieceKind::Pawn:
            return whitePawn_;
        }
    }

    switch (kind)
    {
    case PieceKind::King:
        return blackKing_;

    case PieceKind::Queen:
        return blackQueen_;

    case PieceKind::Rook:
        return blackRook_;

    case PieceKind::Bishop:
        return blackBishop_;

    case PieceKind::Knight:
        return blackKnight_;

    case PieceKind::Pawn:
        return blackPawn_;
    }

    throw std::invalid_argument(
        "Unsupported piece image."
    );
}