#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "inc/test_outputhandler.hpp"
#include "inc/test_utils.hpp"

#include "../src/main/inc/outputhandler.hpp"

extern std::string tmp_file_path;

typedef bool(*testcase)(); // testcase type for creation of array of function pointers

/*

Tests for the OutputHandler class

*/

/*
 * Test print method for basic functionality
 *
 */
bool test_print_basic()
{
    std::cout << "* testing print method for basic functionality";

    // writing

    std::ofstream outp(tmp_file_path);

    husky::OutputHandler *outputhandler = new husky::OutputHandler(&outp);
    outputhandler->print("foobarbaz quxquzz");
    delete outputhandler;

    outp.close();

    // reading

    std::ifstream inp(tmp_file_path);

    std::ostringstream os;
    inp >> os.rdbuf();

    std::string content = os.str();

    inp.close();

    return testStr(content, "foobarbaz quxquzz");
}

/*
 * Tests printline method for basic functionality
 *
 */
bool test_printline_basic()
{
    std::cout << "* testing printline method for basic functionality";

    // writing

    std::ofstream outp(tmp_file_path);

    husky::OutputHandler *outputhandler = new husky::OutputHandler(&outp);
    outputhandler->printline("foobarbaz quxquzz");
    delete outputhandler;

    outp.close();

    // reading

    std::ifstream inp(tmp_file_path);

    std::ostringstream os;
    inp >> os.rdbuf();

    std::string content = os.str();

    inp.close();

    return testStr(content, "foobarbaz quxquzz\n");
}

/*
 * Tests printchar method for basic functionality
 *
 */
bool test_printchar_basic()
{
    std::cout << "* testing printchar method for basic functionality";

    // writing

    std::ofstream outp(tmp_file_path);

    husky::OutputHandler *outputhandler = new husky::OutputHandler(&outp);
    outputhandler->printchar('f');
    delete outputhandler;

    outp.close();

    // reading

    std::ifstream inp(tmp_file_path);

    std::ostringstream os;
    inp >> os.rdbuf();

    std::string content = os.str();

    inp.close();

    return testStr(content, "f");
}

/*
 * Test print, printline, printchar together
 *
 */
bool test_print_printline_printchar_together()
{
    std::cout << "* testing print, printline, printchar together";

    // writing

    std::ofstream outp(tmp_file_path);

    husky::OutputHandler *outputhandler = new husky::OutputHandler(&outp);
    outputhandler->printline("hello");
    outputhandler->print("Husk");
    outputhandler->printchar('y');
    outputhandler->printline("");
    delete outputhandler;

    outp.close();

    // reading

    std::ifstream inp(tmp_file_path);

    std::ostringstream os;
    inp >> os.rdbuf();

    std::string content = os.str();

    inp.close();

    return testStr(content, "hello\nHusky\n");
}


/*
 *
 *
 */
bool test_outputhandler()
{
    bool failed = false;
    int len = 4;

    testcase *funlist = (testcase*) malloc(len * sizeof(testcase));

    funlist[0] = test_print_basic;
    funlist[1] = test_printline_basic;
    funlist[2] = test_printchar_basic;
    funlist[3] = test_print_printline_printchar_together;

    std::cout << "| testing outputhandler" << std::endl;

    for (len--; len >= 0; len--) {
        if (funlist[len]()) failed = true;
    }

    free(funlist);

    return failed;
}
