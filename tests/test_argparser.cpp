#include <iostream>
#include <cstdlib>

#include "inc/test_argparser.hpp"
#include "inc/test_utils.hpp"

#include "../src/main/inc/argparser.hpp"

typedef bool(*testcase)(); // testpack type for creation of array of function pointers

/*

Tests for the ArgParser class

*/

/*
 * Test getFileName method for basic functionality
 *
 */
bool test_getFileName_basic()
{
    std::cout << "* testing getFileName for basic functionality";

    char *argv[] = {
        "hello_world",
        "hi.husky"
    };

    husky::ArgParser *argparser = new husky::ArgParser(2, argv);

    bool retval = testStr(argparser->getFileName(), "hi.husky");

    delete argparser;

    return retval;
}

/*
 * Tests if ArgParser constructor throws 'not enough arguments' error
 *
 */
bool test_throws_not_enough_args()
{
    std::cout << "* testing if constructor throws 'not enough arguments' error";

    char *argv[] = {
        "hello_world"
    };

    try {
        delete new husky::ArgParser(1, argv);

        return true;
    } catch (const char *msg) {
        return testStr(msg, "not enough arguments");
    }
}

/*
 * Tests getCmdName for basic functionality
 *
 */
bool test_getCmdName_basic()
{
    std::cout << "* testing getCmdName for basic functionality";

    char *argv[] = {
        "husky",
        "great.husky"
    };

    husky::ArgParser *argparser = new husky::ArgParser(2, argv);

    bool retval = testStr(argparser->getCmdName(), "husky");

    delete argparser;

    return retval;
}


/*
 *
 *
 */
bool test_argparser()
{
    bool failed = false;
    int len = 3;

    testcase *funlist = (testcase*) malloc(len * sizeof(testcase));

    funlist[0] = test_getFileName_basic;
    funlist[1] = test_getCmdName_basic;
    funlist[2] = test_throws_not_enough_args;

    std::cout << "| testing argparser" << std::endl;

    for (len--; len >= 0; len--) {
        if (funlist[len]()) failed = true;
    }

    free(funlist);

    return failed;
}
