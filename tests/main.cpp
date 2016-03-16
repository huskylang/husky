#include <iostream>

#include "inc/test_inputhandler.hpp"
#include "inc/test_argparser.hpp"
#include "inc/test_outputhandler.hpp"
#include "inc/test_filehandler.hpp"

#include "datatypes/inc/test_string.hpp"
#include "datatypes/inc/test_atom.hpp"

/*
 * Path to the tmp_file
 */
//
std::string tmp_file_path = "/tmp/huskylang_test_asdfasdf_31221";
//


typedef bool(*testpack)(); // testpack type for creation of array of function pointers

int main()
{
    bool failed = false;

    int i;

    int len = 6; // add one for your test

    testpack *funlist = (testpack*) malloc(len * sizeof(testpack));

    // registration of the tests

    funlist[0] = test_inputhandler;
    funlist[1] = test_argparser;
    funlist[2] = test_outputhandler;
    funlist[3] = test_filehandler;
    funlist[4] = test_string_datatype;
    funlist[5] = test_atom_datatype;

    //

    std::cout << "Testing Husky Programming Language" << std::endl \
              << "==================================" << std::endl << std::endl;

    for (i = 0; i < len; i++) {
        if ((*funlist[i])()) failed = true;
        std::cout << std::endl;
    }

    free(funlist);

    if (failed) {
        std::cout << "FAILED" << std::endl;
        return 1;
    } else {
        std::cout << "PASSED" << std::endl;
        return 0;
    }
}
