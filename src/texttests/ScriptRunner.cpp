#include "scriptRunner.hpp"

#include "../io/boardParser.hpp"
#include "../io/boardPrinter.hpp"

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::string ScriptRunner::run(const std::string& script)
{
    std::istringstream input(script);
    std::string line;

    std::vector<std::string> boardLines;
    bool readingBoard = false;

    while (std::getline(input, line))
    {
        if (line == "Board")
        {
            readingBoard = true;
            continue;
        }

        if (line == "print board")
        {
            if (boardLines.empty())
            {
                throw std::runtime_error("board_missing");
            }

            std::string boardText;

            for (std::size_t i = 0; i < boardLines.size(); ++i)
            {
                boardText += boardLines[i];

                if (i + 1 < boardLines.size())
                {
                    boardText += '\n';
                }
            }

            const Board board = BoardParser::parse(boardText);
            return BoardPrinter::print(board);
        }

        if (readingBoard && !line.empty())
        {
            boardLines.push_back(line);
        }
    }

    throw std::runtime_error("print_board_command_missing");
}