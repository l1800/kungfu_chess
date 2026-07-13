#pragma once

#include "board.hpp"

#include <string>

class BoardPrinter
{
public:
    static std::string print(const Board& board);
};