#pragma once

#include "renderer.hpp"

#include "../engine/gameEngine.hpp"
#include "../input/controller.hpp"

class GameView
{
public:
    GameView(
        Controller& controller,
        GameEngine& gameEngine,
        Renderer& renderer
    );

    void onClick(int x, int y);

    void draw() const;

private:
    Controller& controller_;
    GameEngine& gameEngine_;
    Renderer& renderer_;
};