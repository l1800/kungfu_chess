#pragma once

#include "../model/position.hpp"

class MoveRequester
{
public:
    virtual ~MoveRequester() = default;

    virtual void requestMove(
        const Position& source,
        const Position& destination
    ) = 0;
};