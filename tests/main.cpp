#include <iostream>

#include "inc/test_inputhandler.hpp"

typedef bool(*testpack)(); // testpack type for creation of array of function pointers

int main()
{
    bool failed = false;

    int len = 1; // add one for your test

    testpack *funlist = (testpack*) malloc(len * sizeof(testpack));

    // registration of the tests

    funlist[0] = test_inputhandler;

    //

    std::cout << "Testing Husky Programming Language" << std::endl << std::endl;

    for (len--; len >= 0; len--) {
        if ((*funlist[len])()) failed = true;
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
