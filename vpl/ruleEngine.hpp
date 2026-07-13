#pragma once

#include "board.hpp"
#include "position.hpp"

#include <string>

struct MoveValidation
{
    bool isValid;
    std::string reason;
};

class RuleEngine
{
public:
    virtual ~RuleEngine() = default;

    virtual MoveValidation validateMove(
        const Board& board,
        const Position& source,
        const Position& destination
    ) const;
};