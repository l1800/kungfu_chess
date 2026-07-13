#include "ScriptRunner.hpp"

#include "../engine/gameEngine.hpp"
#include "../input/boardMapper.hpp"
#include "../input/controller.hpp"
#include "../io/boardParser.hpp"
#include "../io/boardPrinter.hpp"
#include "../realtime/realTimeArbiter.hpp"
#include "../rules/ruleEngine.hpp"

#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    bool startsWith(
        const std::string& text,
        const std::string& prefix
    )
    {
        return text.rfind(prefix, 0) == 0;
    }

    bool isCommand(const std::string& line)
    {
        return line == "print board" ||
            startsWith(line, "click ") ||
            startsWith(line, "wait ");
    }

    std::string joinLines(
        const std::vector<std::string>& lines
    )
    {
        std::string result;

        for (std::size_t i = 0; i < lines.size(); ++i)
        {
            result += lines[i];

            if (i + 1 < lines.size())
            {
                result += '\n';
            }
        }

        return result;
    }
}

std::string ScriptRunner::run(
    const std::string& script
)
{
    std::istringstream input(script);

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(input, line))
    {
        if (!line.empty() &&
            line.back() == '\r')
        {
            line.pop_back();
        }

        lines.push_back(line);
    }

    if (lines.empty() || lines.front() != "Board")
    {
        throw std::invalid_argument(
            "script_must_start_with_board"
        );
    }

    std::vector<std::string> boardLines;

    std::size_t index = 1;

    while (index < lines.size())
    {
        const std::string& current = lines[index];

        if (current.empty())
        {
            ++index;
            break;
        }

        if (isCommand(current))
        {
            break;
        }

        boardLines.push_back(current);
        ++index;
    }

    if (boardLines.empty())
    {
        throw std::invalid_argument(
            "board_definition_missing"
        );
    }

    Board board =
        BoardParser::parse(joinLines(boardLines));

    RuleEngine ruleEngine;
    RealTimeArbiter realTimeArbiter(board);

    GameEngine gameEngine(
        board,
        ruleEngine,
        realTimeArbiter
    );

    BoardMapper mapper(
        board.width(),
        board.height()
    );

    Controller controller(
        board,
        mapper,
        gameEngine
    );

    std::string output;
    bool hasPrintedBoard = false;

    for (; index < lines.size(); ++index)
    {
        const std::string& command = lines[index];

        if (command.empty())
        {
            continue;
        }

        if (startsWith(command, "click "))
        {
            std::istringstream commandStream(command);

            std::string commandName;
            int x = 0;
            int y = 0;

            commandStream >> commandName >> x >> y;

            if (!commandStream ||
                commandName != "click")
            {
                throw std::invalid_argument(
                    "invalid_click_command"
                );
            }

            controller.click(x, y);
            continue;
        }

        if (startsWith(command, "wait "))
        {
            std::istringstream commandStream(command);

            std::string commandName;
            int milliseconds = 0;

            commandStream >>
                commandName >>
                milliseconds;

            if (!commandStream ||
                commandName != "wait")
            {
                throw std::invalid_argument(
                    "invalid_wait_command"
                );
            }

            gameEngine.wait(milliseconds);
            continue;
        }

        if (command == "print board")
        {
            if (hasPrintedBoard)
            {
                output += "\n\n";
            }

            output += BoardPrinter::print(board);
            hasPrintedBoard = true;
            continue;
        }

        throw std::invalid_argument(
            "unknown_script_command"
        );
    }

    return output;
}