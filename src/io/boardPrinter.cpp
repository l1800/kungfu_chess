#include "BoardPrinter.hpp"


std::string BoardPrinter::print(
    const Board& board
)
{
    std::string output;


    for (int r = 0; r < board.height(); r++)
    {
        for (int c = 0; c < board.width(); c++)
        {
            output += board.getCell(r, c);

            if (c < board.width() - 1)
                output += " ";
        }


        if (r < board.height() - 1)
            output += "\n";
    }


    return output;
}