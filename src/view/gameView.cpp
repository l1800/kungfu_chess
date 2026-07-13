#include "gameView.hpp"

GameView::GameView(
    Controller& controller,
    GameEngine& gameEngine,
    Renderer& renderer
)
    : controller_(controller),
    gameEngine_(gameEngine),
    renderer_(renderer)
{
}

void GameView::onClick(int x, int y)
{
    controller_.click(x, y);
}

void GameView::draw() const
{
    const GameSnapshot snapshot =
        gameEngine_.snapshot(
            controller_.selectedCell()
        );

    renderer_.draw(snapshot);
}
