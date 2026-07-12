#include "../../src/io/boardParser.hpp"
#include <cassert>
#include <stdexcept>
#include <string>

int main()
{
    {
        const std::string text =
            ". .\n"
            "wK .";

        Board board = BoardParser::parse(text);

        assert(board.width() == 2);
        assert(board.height() == 2);
    }

    {
        const std::string text =
            ". . .\n"
            ". .";

        bool threw = false;

        try
        {
            BoardParser::parse(text);
        }
        catch (const std::runtime_error&)
        {
            threw = true;
        }

        assert(threw);
    }

    {
        const std::string text = "XX .";

        bool threw = false;

        try
        {
            BoardParser::parse(text);
        }
        catch (const std::runtime_error&)
        {
            threw = true;
        }

        assert(threw);
    }

    return 0;
}