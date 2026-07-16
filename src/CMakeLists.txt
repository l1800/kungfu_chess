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

    graphics/img.cpp

    view/renderer.cpp
    view/gameView.cpp
    view/imageCatalog.cpp
    view/imgRenderTarget.cpp

    texttests/ScriptRunner.cpp
)

target_include_directories(
    kungfu_chess
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set(OPENCV_DIR "${CMAKE_SOURCE_DIR}/OpenCV_451")
set(OPENCV_INCLUDE_DIR "${OPENCV_DIR}/include")
set(OPENCV_LIB_DIR "${OPENCV_DIR}/bin")

target_include_directories(
    kungfu_chess
    PUBLIC
        ${OPENCV_INCLUDE_DIR}
)

target_link_directories(
    kungfu_chess
    PRIVATE
        ${OPENCV_LIB_DIR}
)

target_link_libraries(
    kungfu_chess
    PRIVATE
        $<$<CONFIG:Debug>:${OPENCV_LIB_DIR}/opencv_world451d.lib>
        $<$<CONFIG:Release>:${OPENCV_LIB_DIR}/opencv_world451.lib>
)
add_executable(
    kungfu_chess_app
    main.cpp
)

target_link_libraries(
    kungfu_chess_app
    PRIVATE
        kungfu_chess
)

if(WIN32)
    add_custom_command(
        TARGET kungfu_chess_app
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<$<CONFIG:Debug>:${OPENCV_LIB_DIR}/opencv_world451d.dll>
            $<$<CONFIG:Release>:${OPENCV_LIB_DIR}/opencv_world451.dll>
            $<TARGET_FILE_DIR:kungfu_chess_app>
    )
endif()
add_custom_command(
    TARGET kungfu_chess_app
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:kungfu_chess_app>/assets"
)
target_compile_definitions(
    kungfu_chess
    PUBLIC
        ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets"
)