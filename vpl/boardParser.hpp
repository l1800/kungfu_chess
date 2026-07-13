#pragma once

#include "board.hpp"

#include <string>

class BoardParser
{
public:
    static Board parse(const std::string& text);

private:
    static bool isValidToken(
        const std::string& token
    );

    static Piece parsePiece(
        const std::string& token,
        int id,
        const Position& position
    );
};