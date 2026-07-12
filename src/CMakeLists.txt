add_library(kungfu_chess
    model/Position.cpp
    model/Board.cpp
    io/BoardParser.cpp
    io/BoardPrinter.cpp
)

target_include_directories(kungfu_chess
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)