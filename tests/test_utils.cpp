#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "../src/main/inc/filehandler.hpp"
#include "../src/main/inc/outputhandler.hpp"
#include "../src/main/inc/inputhandler.hpp"

#include "../src/parser/inc/parser.hpp"

#include "inc/test_utils.hpp"

extern std::string tmp_file_path;

using namespace husky;

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
    std::cout << std::endl;

    if (result == to_see) {
        std::cout << "ok" << std::endl;
        return false;
    }

    std::cout << "'" << result << "' != '" << to_see << "'" << std::endl;

    return true;
}

/*
 * Tests character output of a method or a function
 *
 */
bool testChar(char ch, const char ch_to_see)
{
    std::cout << std::endl;

    if (ch == ch_to_see) {
        std::cout << "ok" << std::endl;
        return false;
    }

    std::cout << "'" << ch << "' != '" << ch_to_see << "'" << std::endl;

    return true;
}

/*
 * Tests boolean output of a method or a function
 *
 */
bool testBool(bool result, bool to_see)
{
    std::cout << std::endl;

    if (result == to_see) {
        std::cout << "ok" << std::endl;
        return false;
    }

    std::cout << result << " != " << to_see << std::endl;

    return true;
}

/*
 * Tests integer output of a method or a function
 *
 */
bool testInt(long long int result, long long int to_see)
{
    std::cout << std::endl;

    if (result == to_see) {
        std::cout << "ok" << std::endl;
        return false;
    }

    std::cout << result << " != " << to_see;

    return true;
}


/**
 * and some helper tools
 *
 */

/*
 * This is an is_end function which always returns true
 *
 */
bool empty_is_end(char)
{
    return true;
}


FileHandler *create_filehandler()
{
    return new FileHandler(tmp_file_path.c_str());
}

InputHandler *create_inhandler()
{
    std::ifstream inp((tmp_file_path + "_1").c_str());

    return new InputHandler(&inp);
}

OutputHandler *create_outhandler()
{
    std::ofstream outp((tmp_file_path + "_2").c_str());

    return new OutputHandler(&outp);
}

Parser *create_parser(bool (*is_end)(char))
{
    return new Parser(
        create_filehandler(), create_outhandler(), create_inhandler(), is_end
    );
}

void cleanup_parser(Parser *parser)
{
    delete parser->filehandler;
    delete parser->outhandler;
    delete parser->inhandler;

    parser->clean();
    delete parser;
}
