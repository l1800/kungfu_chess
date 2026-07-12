#pragma once

#include "../model/Board.hpp"

#include <string>


class BoardParser
{
public:

    static Board parse(
        const std::string& text
    );


private:

    static bool validToken(
        const std::string& token
    );
};