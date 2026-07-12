#include "../../src/texttests/scriptRunner.hpp"

#include <cassert>
#include <string>

int main()
{
    const std::string script =
        "Board\n"
        ". . .\n"
        ". wK .\n"
        ". . .\n"
        "\n"
        "print board\n";

    const std::string expected =
        ". . .\n"
        ". wK .\n"
        ". . .";

    const std::string actual = ScriptRunner::run(script);

    assert(actual == expected);

    return 0;
}