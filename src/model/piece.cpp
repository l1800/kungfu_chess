#include "piece.hpp"

#include <stdexcept>

Piece::Piece(
    int id,
    PieceColor color,
    PieceKind kind,
    const Position& cell
)
    : id_(id),
    color_(color),
    kind_(kind),
    cell_(cell),
    state_(PieceState::Idle)
{
    if (id < 0)
    {
        throw std::invalid_argument(
            "piece_id_must_be_non_negative"
        );
    }
}

int Piece::id() const
{
    return id_;
}

PieceColor Piece::color() const
{
    return color_;
}

PieceKind Piece::kind() const
{
    return kind_;
}

const Position& Piece::cell() const
{
    return cell_;
}

PieceState Piece::state() const
{
    return state_;
}

void Piece::setCell(const Position& cell)
{
    cell_ = cell;
}

void Piece::setState(PieceState state)
{
    state_ = state;
}

std::string pieceToToken(const Piece& piece)
{
    std::string token =
        piece.color() == PieceColor::White
        ? "w"
        : "b";

    switch (piece.kind())
    {
    case PieceKind::King:
        token += "K";
        break;

    case PieceKind::Queen:
        token += "Q";
        break;

    case PieceKind::Rook:
        token += "R";
        break;

    case PieceKind::Bishop:
        token += "B";
        break;

    case PieceKind::Knight:
        token += "N";
        break;

    case PieceKind::Pawn:
        token += "P";
        break;
    }

    return token;
}