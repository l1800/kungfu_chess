#include "BoardParser.hpp"

#include <sstream>
#include <stdexcept>
#include <set>
#include <vector>


Board BoardParser::parse(
    const std::string& text
)
{
    std::stringstream stream(text);

    std::string line;

    std::vector<std::vector<std::string>> rows;


    while (std::getline(stream, line))
    {
        if (line.empty())
            continue;


        std::stringstream rowStream(line);

        std::vector<std::string> row;

        std::string token;


        while (rowStream >> token)
        {
            if (!validToken(token))
                throw std::runtime_error(
                    "invalid_piece_token"
                );

            row.push_back(token);
        }


        rows.push_back(row);
    }


    if (rows.empty())
        throw std::runtime_error(
            "empty_board"
        );


    size_t width = rows[0].size();


    for (const auto& row : rows)
    {
        if (row.size() != width)
            throw std::runtime_error(
                "inconsistent_row_length"
            );
    }


    Board board(
        static_cast<int>(width),
        static_cast<int>(rows.size())
    );


    for (int r = 0; r < rows.size(); r++)
    {
        for (int c = 0; c < rows[r].size(); c++)
        {
            board.setCell(
                r,
                c,
                rows[r][c]
            );
        }
    }


    return board;
}



bool BoardParser::validToken(
    const std::string& token
)
{
    static const std::set<std::string> valid =
    {
        ".",
        "wK","wQ","wR","wB","wN","wP",
        "bK","bQ","bR","bB","bN","bP"
    };


    return valid.find(token) != valid.end();
}