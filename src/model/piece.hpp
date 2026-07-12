#pragma once

#include "position.hpp"

#include <string>

enum class PieceColor
{
    White,
    Black
};

enum class PieceKind
{
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn
};

enum class PieceState
{
    Idle,
    Moving,
    Captured
};

class Piece
{
public:
    Piece(
        int id,
        PieceColor color,
        PieceKind kind,
        const Position& cell
    );

    int id() const;
    PieceColor color() const;
    PieceKind kind() const;
    const Position& cell() const;
    PieceState state() const;

    void setCell(const Position& cell);
    void setState(PieceState state);

private:
    int id_;
    PieceColor color_;
    PieceKind kind_;
    Position cell_;
    PieceState state_;
};

std::string pieceToToken(const Piece& piece);