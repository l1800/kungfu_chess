#pragma once

#include "../model/Board.hpp"

#include <string>


class BoardPrinter
{
public:

    static std::string print(
        const Board& board
    );
};