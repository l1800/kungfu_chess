function(add_kungfu_unit_test test_name source_file)
    add_executable(${test_name}
        ${source_file}
    )

    target_link_libraries(${test_name}
        PRIVATE
            kungfu_chess
            GTest::gtest_main
    )

    add_test(
        NAME ${test_name}
        COMMAND $<TARGET_FILE:${test_name}>
    )
endfunction()

add_kungfu_unit_test(
    PositionTest
    positionTest.cpp
)

add_kungfu_unit_test(
    PieceTest
    pieceTest.cpp
)

add_kungfu_unit_test(
    BoardTest
    boardTest.cpp
)

add_kungfu_unit_test(
    BoardParserTest
    BoardParserTest.cpp
)

add_kungfu_unit_test(
    BoardPrinterTest
    BoardPrinterTest.cpp
)