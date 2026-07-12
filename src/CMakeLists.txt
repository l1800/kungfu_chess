add_library(kungfu_chess
    model/position.cpp
    model/board.cpp
    io/boardParser.cpp
    io/boardPrinter.cpp
    texttests/ScriptRunner.cpp
)

target_include_directories(kungfu_chess
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)