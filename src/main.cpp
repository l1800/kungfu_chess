#include "engine/gameEngine.hpp"
#include "input/boardMapper.hpp"
#include "input/controller.hpp"
#include "io/boardParser.hpp"
#include "realtime/realTimeArbiter.hpp"
#include "rules/ruleEngine.hpp"
#include "view/gameView.hpp"
#include "view/renderTarget.hpp"
#include "view/renderer.hpp"

#include <exception>
#include <iostream>
#include <string>

namespace
{
    class ConsoleRenderTarget : public RenderTarget
    {
    public:
        void beginFrame(
            int boardWidth,
            int boardHeight,
            int cellSize
        ) override
        {
            std::cout
                << "Board: "
                << boardWidth
                << "x"
                << boardHeight
                << ", cell size: "
                << cellSize
                << '\n';
        }

        void drawPiece(
            const PieceSnapshot& piece
        ) override
        {
            std::cout
                << "Piece "
                << piece.id
                << " at pixel ("
                << piece.pixelX
                << ", "
                << piece.pixelY
                << ")\n";
        }

        void drawSelection(
            const Position& selectedCell,
            int cellSize
        ) override
        {
            std::cout
                << "Selected cell: row="
                << selectedCell.row()
                << ", col="
                << selectedCell.col()
                << ", cell size="
                << cellSize
                << '\n';
        }

        void drawGameOver() override
        {
            std::cout << "Game over\n";
        }

        void endFrame() override
        {
            std::cout << "Frame finished\n";
        }
    };
}

int main()
{
    try
    {
        const std::string boardText =
            "wR . bK\n"
            ". . .\n"
            ". . .";

        Board board =
            BoardParser::parse(boardText);

        RuleEngine ruleEngine;

        RealTimeArbiter realTimeArbiter(
            board
        );

        GameEngine gameEngine(
            board,
            ruleEngine,
            realTimeArbiter
        );

        BoardMapper boardMapper(
            board.width(),
            board.height()
        );

        Controller controller(
            board,
            boardMapper,
            gameEngine
        );

        ConsoleRenderTarget renderTarget;

        Renderer renderer(
            renderTarget
        );

        GameView gameView(
            controller,
            gameEngine,
            renderer
        );

        /*
         * ציור מצב התחלתי.
         */
        gameView.draw();

        /*
         * דוגמת נתיב קלט אמיתי:
         * בחירת הצריח ואז בחירת יעד.
         */
        gameView.onClick(50, 50);
        gameView.onClick(150, 50);

        /*
         * קידום זמן מדומה של תא אחד.
         */
        gameEngine.wait(1000);

        /*
         * ציור מצב לאחר התנועה.
         */
        gameView.draw();

        return 0;
    }
    catch (const std::exception& exception)
    {
        std::cerr
            << "Application error: "
            << exception.what()
            << '\n';

        return 1;
    }
}