#pragma once

#include "piece.hpp"
#include "position.hpp"

#include <optional>
#include <vector>

struct PieceSnapshot
{
    int id;
    PieceColor color;
    PieceKind kind;
    PieceState state;

    double pixelX;
    double pixelY;
};

struct GameSnapshot
{
    int boardWidth;
    int boardHeight;
    int cellSize;

    std::vector<PieceSnapshot> pieces;

    std::optional<Position> selectedCell;

    bool gameOver;
};