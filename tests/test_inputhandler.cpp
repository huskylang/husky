#include <string>
#include <iostream>
#include <fstream>

#include "inc/test_inputhandler.hpp"
#include "inc/test_utils.hpp"

#include "../src/main/inc/inputhandler.hpp"

extern std::string tmp_file_path;

typedef bool(*testcase)(); // testcase type for creation of array of function pointers


/*

Tests for inputhandler

*/

/*
 * Test getLine for basic functionality
 *
 */
bool test_getLine_basic()
{
    std::cout << "* test getLine basic functionality";

    system(("echo 'hello world\nthe best' > " + tmp_file_path).c_str());

    std::ifstream inp(tmp_file_path);

    husky::InputHandler *handler = new husky::InputHandler(&inp);

    bool status = testStr(handler->getLine(), "hello world");

    delete handler;

    return status;
}

/*
 * Test getLine for 1 character functionality
 *
 */
bool test_getLine_1_ch()
{
    std::cout << "* test getLine one character functionality";

    system(("echo 'h' > " + tmp_file_path).c_str());

    std::ifstream inp(tmp_file_path);

    husky::InputHandler *handler = new husky::InputHandler(&inp);

    bool status = testStr(handler->getLine(), "h");

    delete handler;

    return status;
}

/*
 * Test getLine for one line functionality
 *
 */
bool test_getLine_1_line()
{
    std::cout << "* test getLine one line functionality";

    system(("echo 'foobarbaz' > " + tmp_file_path).c_str());

    std::ifstream inp(tmp_file_path);

    husky::InputHandler *handler = new husky::InputHandler(&inp);

    bool status = testStr(handler->getLine(), "foobarbaz");

    delete handler;

    return status;
}


/*
 *
 *
 */
bool test_inputhandler()
{
    bool failed = false;
    int len = 3;

    testcase *funlist = (testcase*) malloc(len * sizeof(testcase));

    funlist[0] = test_getLine_basic;
    funlist[1] = test_getLine_1_ch;
    funlist[2] = test_getLine_1_line;

    std::cout << "| testing inputhandler" << std::endl;

    for (len--; len >= 0; len--) {
        if (funlist[len]()) failed = true;
    }

    free(funlist);

    return failed;
}
