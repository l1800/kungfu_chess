#include "boardParser.hpp"

#include <sstream>
#include <stdexcept>
#include <vector>

Board BoardParser::parse(const std::string& text)
{
    std::istringstream input(text);
    std::string line;

    std::vector<std::vector<std::string>> rows;

    while (std::getline(input, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream rowStream(line);
        std::vector<std::string> row;
        std::string token;

        while (rowStream >> token)
        {
            if (!isValidToken(token))
            {
                throw std::invalid_argument(
                    "invalid_piece_token"
                );
            }

            row.push_back(token);
        }

        if (!row.empty())
        {
            rows.push_back(row);
        }
    }

    if (rows.empty())
    {
        throw std::invalid_argument("empty_board");
    }

    const int width =
        static_cast<int>(rows.front().size());

    for (const auto& row : rows)
    {
        if (static_cast<int>(row.size()) != width)
        {
            throw std::invalid_argument(
                "inconsistent_row_length"
            );
        }
    }

    Board board(
        width,
        static_cast<int>(rows.size())
    );

    int nextPieceId = 0;

    for (int row = 0; row < board.height(); ++row)
    {
        for (int col = 0; col < board.width(); ++col)
        {
            const std::string& token = rows[row][col];

            if (token == ".")
            {
                continue;
            }

            const Position position(row, col);

            board.addPiece(
                parsePiece(
                    token,
                    nextPieceId,
                    position
                )
            );

            ++nextPieceId;
        }
    }

    return board;
}

bool BoardParser::isValidToken(
    const std::string& token
)
{
    return token == "." ||
        token == "wK" ||
        token == "wQ" ||
        token == "wR" ||
        token == "wB" ||
        token == "wN" ||
        token == "wP" ||
        token == "bK" ||
        token == "bQ" ||
        token == "bR" ||
        token == "bB" ||
        token == "bN" ||
        token == "bP";
}

Piece BoardParser::parsePiece(
    const std::string& token,
    int id,
    const Position& position
)
{
    const PieceColor color =
        token[0] == 'w'
        ? PieceColor::White
        : PieceColor::Black;

    PieceKind kind;

    switch (token[1])
    {
    case 'K':
        kind = PieceKind::King;
        break;

    case 'Q':
        kind = PieceKind::Queen;
        break;

    case 'R':
        kind = PieceKind::Rook;
        break;

    case 'B':
        kind = PieceKind::Bishop;
        break;

    case 'N':
        kind = PieceKind::Knight;
        break;

    case 'P':
        kind = PieceKind::Pawn;
        break;

    default:
        throw std::invalid_argument(
            "invalid_piece_token"
        );
    }

    return Piece(id, color, kind, position);
}