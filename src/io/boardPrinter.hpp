#pragma once

#include "../model/board.hpp"

#include <string>

class BoardPrinter
{
public:
    static std::string print(const Board& board);
};