# CMake generated Testfile for 
# Source directory: C:/kungfu_chess/tests/integration
# Build directory: C:/kungfu_chess/build/tests/integration
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[ScriptRunnerTest]=] "C:/kungfu_chess/build/tests/integration/Debug/ScriptRunnerTest.exe")
  set_tests_properties([=[ScriptRunnerTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/kungfu_chess/tests/integration/CMakeLists.txt;11;add_test;C:/kungfu_chess/tests/integration/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[ScriptRunnerTest]=] "C:/kungfu_chess/build/tests/integration/Release/ScriptRunnerTest.exe")
  set_tests_properties([=[ScriptRunnerTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/kungfu_chess/tests/integration/CMakeLists.txt;11;add_test;C:/kungfu_chess/tests/integration/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[ScriptRunnerTest]=] "C:/kungfu_chess/build/tests/integration/MinSizeRel/ScriptRunnerTest.exe")
  set_tests_properties([=[ScriptRunnerTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/kungfu_chess/tests/integration/CMakeLists.txt;11;add_test;C:/kungfu_chess/tests/integration/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[ScriptRunnerTest]=] "C:/kungfu_chess/build/tests/integration/RelWithDebInfo/ScriptRunnerTest.exe")
  set_tests_properties([=[ScriptRunnerTest]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/kungfu_chess/tests/integration/CMakeLists.txt;11;add_test;C:/kungfu_chess/tests/integration/CMakeLists.txt;0;")
else()
  add_test([=[ScriptRunnerTest]=] NOT_AVAILABLE)
endif()
