add_executable(ScriptRunnerTest
    ScriptRunnerTest.cpp
)

target_link_libraries(ScriptRunnerTest
    PRIVATE
    kungfu_chess
)

add_test(
    NAME ScriptRunnerTest
    COMMAND $<TARGET_FILE:ScriptRunnerTest>
)