#include "board.hpp"

#include <stdexcept>

Board::Board(int width, int height)
    : width_(width),
    height_(height),
    cells_(
        height,
        std::vector<std::optional<Piece>>(width)
    )
{
    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument(
            "board_dimensions_must_be_positive"
        );
    }
}

int Board::width() const
{
    return width_;
}

int Board::height() const
{
    return height_;
}

bool Board::isInside(const Position& position) const
{
    return position.row() >= 0 &&
        position.row() < height_ &&
        position.col() >= 0 &&
        position.col() < width_;
}

const Piece* Board::getPieceAt(
    const Position& position
) const
{
    if (!isInside(position))
    {
        return nullptr;
    }

    const auto& cell =
        cells_[position.row()][position.col()];

    return cell.has_value()
        ? &cell.value()
        : nullptr;
}

Piece* Board::getPieceAt(
    const Position& position
)
{
    if (!isInside(position))
    {
        return nullptr;
    }

    auto& cell =
        cells_[position.row()][position.col()];

    return cell.has_value()
        ? &cell.value()
        : nullptr;
}

void Board::addPiece(const Piece& piece)
{
    const Position& position = piece.cell();

    if (!isInside(position))
    {
        throw std::invalid_argument(
            "piece_outside_board"
        );
    }

    if (getPieceAt(position) != nullptr)
    {
        throw std::invalid_argument(
            "cell_already_occupied"
        );
    }

    if (containsPieceId(piece.id()))
    {
        throw std::invalid_argument(
            "duplicate_piece_id"
        );
    }

    cells_[position.row()][position.col()] = piece;
}

void Board::removePiece(const Position& position)
{
    if (!isInside(position))
    {
        throw std::invalid_argument(
            "position_outside_board"
        );
    }

    cells_[position.row()][position.col()].reset();
}

void Board::movePiece(
    const Position& source,
    const Position& destination
)
{
    if (!isInside(source) || !isInside(destination))
    {
        throw std::invalid_argument(
            "position_outside_board"
        );
    }

    auto& sourceCell =
        cells_[source.row()][source.col()];

    auto& destinationCell =
        cells_[destination.row()][destination.col()];

    if (!sourceCell.has_value())
    {
        throw std::invalid_argument("empty_source");
    }

    if (destinationCell.has_value())
    {
        throw std::invalid_argument(
            "destination_occupied"
        );
    }

    Piece movingPiece = sourceCell.value();
    movingPiece.setCell(destination);

    destinationCell = movingPiece;
    sourceCell.reset();
}

bool Board::containsPieceId(int id) const
{
    for (const auto& row : cells_)
    {
        for (const auto& cell : row)
        {
            if (cell.has_value() &&
                cell->id() == id)
            {
                return true;
            }
        }
    }

    return false;
}