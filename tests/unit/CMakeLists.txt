set(GTEST_ROOT
    "${CMAKE_SOURCE_DIR}/external/googletest/googletest"
)

add_library(local_gtest STATIC
    "${GTEST_ROOT}/src/gtest-all.cc"
)

target_include_directories(local_gtest
    PUBLIC
        "${GTEST_ROOT}/include"
        "${GTEST_ROOT}"
)

add_library(local_gtest_main STATIC
    "${GTEST_ROOT}/src/gtest_main.cc"
)

target_include_directories(local_gtest_main
    PUBLIC
        "${GTEST_ROOT}/include"
        "${GTEST_ROOT}"
)

target_link_libraries(local_gtest_main
    PUBLIC
        local_gtest
)


add_executable(BoardParserTest
    BoardParserTest.cpp
)

target_link_libraries(BoardParserTest
    PRIVATE
        kungfu_chess
        local_gtest_main
)

add_test(
    NAME BoardParserTest
    COMMAND $<TARGET_FILE:BoardParserTest>
)


add_executable(BoardPrinterTest
    BoardPrinterTest.cpp
)

target_link_libraries(BoardPrinterTest
    PRIVATE
        kungfu_chess
        local_gtest_main
)

add_test(
    NAME BoardPrinterTest
    COMMAND $<TARGET_FILE:BoardPrinterTest>
)