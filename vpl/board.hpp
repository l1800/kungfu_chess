#pragma once

#include "piece.hpp"
#include "position.hpp"

#include <optional>
#include <vector>

class Board
{
public:
    Board(int width, int height);

    int width() const;
    int height() const;

    bool isInside(const Position& position) const;

    const Piece* getPieceAt(const Position& position) const;
    Piece* getPieceAt(const Position& position);

    void addPiece(const Piece& piece);
    void removePiece(const Position& position);

    void movePiece(
        const Position& source,
        const Position& destination
    );

private:
    int width_;
    int height_;

    std::vector<
        std::vector<std::optional<Piece>>
    > cells_;

    bool containsPieceId(int id) const;
};