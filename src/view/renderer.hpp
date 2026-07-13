#pragma once

#include "renderTarget.hpp"

#include "../model/gameSnapshot.hpp"

class Renderer
{
public:
    explicit Renderer(RenderTarget& target);

    void draw(
        const GameSnapshot& snapshot
    ) const;

private:
    RenderTarget& target_;
};