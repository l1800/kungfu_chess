#include "../../src/io/boardParser.hpp"

#include <cassert>
#include <stdexcept>
#include <string>

int main()
{
    // BoardParser accepts a valid rectangular board.
    {
        const std::string input =
            ". . .\n"
            ". wK .\n"
            ". . .";

        const Board board = BoardParser::parse(input);

        assert(board.width() == 3);
        assert(board.height() == 3);
    }

    // BoardParser rejects rows with different lengths.
    {
        const std::string input =
            ". . .\n"
            ". .\n"
            ". . .";

        bool exceptionThrown = false;

        try
        {
            BoardParser::parse(input);
        }
        catch (const std::runtime_error&)
        {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    // BoardParser rejects an unknown token.
    {
        const std::string input =
            ". . .\n"
            ". XX .\n"
            ". . .";

        bool exceptionThrown = false;

        try
        {
            BoardParser::parse(input);
        }
        catch (const std::runtime_error&)
        {
            exceptionThrown = true;
        }

        assert(exceptionThrown);
    }

    return 0;
}