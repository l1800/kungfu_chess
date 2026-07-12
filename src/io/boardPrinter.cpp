#include "boardPrinter.hpp"

#include "../model/piece.hpp"

std::string BoardPrinter::print(const Board& board)
{
    std::string output;

    for (int row = 0; row < board.height(); ++row)
    {
        for (int col = 0; col < board.width(); ++col)
        {
            const Piece* piece =
                board.getPieceAt(
                    Position(row, col)
                );

            output +=
                piece == nullptr
                ? "."
                : pieceToToken(*piece);

            if (col + 1 < board.width())
            {
                output += " ";
            }
        }

        if (row + 1 < board.height())
        {
            output += "\n";
        }
    }

    return output;
}