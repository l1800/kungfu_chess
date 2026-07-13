#include "ScriptRunner.hpp"

#include <cctype>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    std::string trim(const std::string& value)
    {
        std::size_t start = 0;

        while (start < value.size() &&
            std::isspace(static_cast<unsigned char>(value[start])))
        {
            ++start;
        }

        std::size_t end = value.size();

        while (end > start &&
            std::isspace(static_cast<unsigned char>(value[end - 1])))
        {
            --end;
        }

        return value.substr(start, end - start);
    }

    bool isHeader(const std::string& line, const std::string& header)
    {
        return trim(line) == header;
    }

    std::string toScriptFormat(const std::string& rawInput)
    {
        std::istringstream input(rawInput);
        std::string line;

        std::vector<std::string> boardLines;
        std::vector<std::string> commandLines;

        bool inBoard = false;
        bool inCommands = false;

        while (std::getline(input, line))
        {
            if (!line.empty() && line.back() == '\r')
            {
                line.pop_back();
            }

            if (isHeader(line, "Board:") || isHeader(line, "Board"))
            {
                inBoard = true;
                inCommands = false;
                continue;
            }

            if (isHeader(line, "Commands:") || isHeader(line, "Commands"))
            {
                inCommands = true;
                inBoard = false;
                continue;
            }

            if (inBoard)
            {
                const std::string normalized = trim(line);

                if (!normalized.empty())
                {
                    boardLines.push_back(normalized);
                }

                continue;
            }

            if (inCommands)
            {
                const std::string normalized = trim(line);

                if (!normalized.empty())
                {
                    commandLines.push_back(normalized);
                }
            }
        }

        std::string script = "Board\n";

        for (const std::string& boardLine : boardLines)
        {
            script += boardLine + "\n";
        }

        script += "\n";

        for (const std::string& commandLine : commandLines)
        {
            script += commandLine + "\n";
        }

        return script;
    }

    std::string mapError(const std::string& message)
    {
        if (message == "invalid_piece_token")
        {
            return "ERROR UNKNOWN_TOKEN";
        }

        if (message == "inconsistent_row_length")
        {
            return "ERROR ROW_WIDTH_MISMATCH";
        }

        return "ERROR " + message;
    }
}

int main()
{
    try
    {
        std::ostringstream buffer;
        buffer << std::cin.rdbuf();

        const std::string script =
            toScriptFormat(buffer.str());

        const std::string output =
            ScriptRunner::run(script);

        std::cout << output;

        return 0;
    }
    catch (const std::invalid_argument& exception)
    {
        std::cout << mapError(exception.what());

        return 0;
    }
    catch (const std::exception&)
    {
        std::cout << "ERROR INTERNAL";

        return 0;
    }
}
