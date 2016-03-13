#include <string>
#include <iostream>
#include <fstream>

#include "inc/test_filehandler.hpp"
#include "inc/test_utils.hpp"

#include "../src/main/inc/filehandler.hpp"

extern std::string tmp_file_path;

typedef bool(*testcase)(); // testacse type for creation of array of function pointers

/*

Tests for the FileHandler class

*/

/*
 * Test getLine method for basic functionality
 *
 */
bool test_filehandler_getLine_basic()
{
    std::cout << "* testing getLine method for basic functionality";

    system(("echo 'foo bar\nbar baz\nbaz qux' > " + tmp_file_path).c_str());

    husky::FileHandler *filehandler = new husky::FileHandler(tmp_file_path);

    bool retval = testStr(filehandler->getLine(), "foo bar");

    delete filehandler;

    return retval;
}

/*
 * Test getChar method for basic functionality
 *
 */
bool test_getChar_basic()
{
    std::cout << "* testing getChar method for basic functionality";

    system(("echo 'foo bar\nbar baz\nbaz qux' > " + tmp_file_path).c_str());

    husky::FileHandler *filehandler = new husky::FileHandler(tmp_file_path);

    bool retval = testChar(filehandler->getChar(), 'f');

    delete filehandler;

    return retval;
}

/*
 * Test eof method of an empty file
 *
 */
bool test_eof_empty()
{
    std::cout << "* testing eof method of an empty file";

    system(("rm -f " + tmp_file_path + " && touch " + tmp_file_path).c_str());

    husky::FileHandler *filehandler = new husky::FileHandler(tmp_file_path);

    filehandler->getLine();

    bool retval = testBool(filehandler->eof(), true);

    delete filehandler;

    return retval;
}

/*
 * Test eof method when it is not eof
 *
 */
bool test_eof_not_eof()
{
    std::cout << "* testing eof method when it is not eof";

    system(("echo 'foobar' > " + tmp_file_path).c_str());

    husky::FileHandler *filehandler = new husky::FileHandler(tmp_file_path);

    bool retval = testBool(filehandler->eof(), false);

    delete filehandler;

    return retval;
}

/*
 * Test eof method when it is eof
 *
 */
bool test_eof_is_eof()
{
    std::cout << "* testing eof method when it is eof";

    system(("echo 'foobar' > " + tmp_file_path).c_str());

    husky::FileHandler *filehandler = new husky::FileHandler(tmp_file_path);

    filehandler->getLine();
    filehandler->getLine();

    bool retval = testBool(filehandler->eof(), true);

    delete filehandler;

    return retval;
}

/*
 * Test if constructor throws 'file not found' error
 *
 */
bool test_throws_file_not_found_error()
{
    std::cout << "* testing if constructor throws 'file not found' error";

    system("rm -f tmp/not_found_file_asdfasdf_322112");

    try {
        delete new husky::FileHandler("tmp/not_found_file_asdfasdf_322112");
    } catch (std::string msg) {
        return testStr(msg, "file: 'tmp/not_found_file_asdfasdf_322112' not found");
    }
}

/*
 *
 *
 */
bool test_filehandler()
{
    bool failed = false;
    int len = 6;

    testcase *funlist = (testcase*) malloc(len * sizeof(testcase));

    funlist[0] = test_filehandler_getLine_basic;
    funlist[1] = test_getChar_basic;
    funlist[2] = test_throws_file_not_found_error;
    funlist[3] = test_eof_empty;
    funlist[4] = test_eof_is_eof;
    funlist[5] = test_eof_not_eof;

    std::cout << "| testing filehandler" << std::endl;

    for (len--; len >= 0; len--) {
        if (funlist[len]()) failed = true;
    }

    free(funlist);

    return failed;
}
