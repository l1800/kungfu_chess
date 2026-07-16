#include "engine/gameEngine.hpp"
#include "input/boardMapper.hpp"
#include "input/controller.hpp"
#include "io/boardParser.hpp"
#include "realtime/realTimeArbiter.hpp"
#include "rules/ruleEngine.hpp"
#include "view/gameView.hpp"
#include "view/imageCatalog.hpp"
#include "view/imgRenderTarget.hpp"
#include "view/renderer.hpp"

#include <opencv2/opencv.hpp>

#include <exception>
#include <iostream>
#include <string>

namespace
{
    constexpr const char* WINDOW_NAME =
        "Kung Fu Chess";

    struct MouseContext
    {
        GameView* gameView;
    };

    void handleMouse(
        int event,
        int x,
        int y,
        int,
        void* userData
    )
    {
        if (event != cv::EVENT_LBUTTONDOWN)
        {
            return;
        }

        MouseContext* context =
            static_cast<MouseContext*>(userData);

        if (context == nullptr ||
            context->gameView == nullptr)
        {
            return;
        }

        context->gameView->onClick(x, y);
    }
}

int main()
{
    try
    {
        const std::string boardText =
            "bR bN bB bQ bK bB bN bR\n"
            "bP bP bP bP bP bP bP bP\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            ". . . . . . . .\n"
            "wP wP wP wP wP wP wP wP\n"
            "wR wN wB wQ wK wB wN wR";

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

        ImageCatalog imageCatalog(
            GameEngine::CELL_SIZE
        );

        ImgRenderTarget renderTarget(
            imageCatalog
        );

        Renderer renderer(
            renderTarget
        );

        GameView gameView(
            controller,
            gameEngine,
            renderer
        );

        /*
         * ציור ראשון יוצר את חלון OpenCV.
         */
        gameView.draw();

        MouseContext mouseContext{
            &gameView
        };

        cv::setMouseCallback(
            WINDOW_NAME,
            handleMouse,
            &mouseContext
        );

        while (true)
        {
            /*
             * קידום זמן מדומה.
             * אין sleep אמיתי.
             */
            gameEngine.wait(16);

            gameView.draw();

            const int key =
                renderTarget.lastKey();

            /*
             * Esc
             */
            if (key == 27)
            {
                break;
            }

            /*
             * סגירת החלון באמצעות X.
             */
            if (cv::getWindowProperty(
                WINDOW_NAME,
                cv::WND_PROP_VISIBLE
            ) < 1)
            {
                break;
            }
        }

        cv::destroyAllWindows();

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