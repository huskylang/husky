#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "inc/test_utils.hpp"

bool testOutput(std::string script, std::string out_to_see)
{
    std::string out;

    std::cout << script << std::endl;

    system(("../bin/husky ./scripts/" + script + " > ../tmp/test.out").c_str());

    std::ifstream outstream("../tmp/test.out");
    std::stringstream buffer;

    buffer << outstream.rdbuf();

    out = buffer.str();

    if (out == out_to_see) {
        std::cout << "ok" << std::endl << std::endl;
    }

    std::cout << "'" << std::endl << out << std::endl << "'" << std::endl;

    std::cout << "/=" << std::endl;

    std::cout << "'" << std::endl << out_to_see << std::endl << "'" << std::endl << std::endl;
}

/*
 * Tests string output of a method or a function
 *
 */
bool testStr(std::string result, std::string to_see)
{
    if (result == to_see) {
        std::cout << std::endl << "ok" << std::endl;
        return false;
    }

    std::cout << "'" << result << "' != '" << to_see << "'" << std::endl;

    return true;
}

/*
 * Tests integer output of a method or a function
 *
 */
bool testInt(long long int result, long long int to_see)
{
    if (result == to_see) {
        std::cout << std::endl << "ok" << std::endl;
        return false;
    }

    std::cout << result << " != " << to_see;

    return true;
}
