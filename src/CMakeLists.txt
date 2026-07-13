add_library(kungfu_chess
    model/position.cpp
    model/piece.cpp
    model/board.cpp

    io/boardParser.cpp
    io/boardPrinter.cpp

    input/boardMapper.cpp
    input/controller.cpp

    rules/pieceRules.cpp
    rules/ruleEngine.cpp

    realtime/motion.cpp
    realtime/realTimeArbiter.cpp

    engine/gameEngine.cpp

    texttests/ScriptRunner.cpp
)

target_include_directories(kungfu_chess
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)