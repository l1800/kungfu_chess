#include "../../src/io/boardParser.hpp"
#include "../../src/io/boardPrinter.hpp"

#include <cassert>
#include <string>

int main()
{
    const std::string original =
        ". . .\n"
        ". wK .\n"
        ". . .";

    const Board board = BoardParser::parse(original);
    const std::string printed = BoardPrinter::print(board);

    assert(printed == original);

    return 0;
}