#include <string>
#include <iostream>
#include <cstdlib>

#include "../../src/parser/inc/parser.hpp"

#include "../../src/parser/datatypes/inc/string.hpp"
#include "../../src/parser/datatypes/inc/abstract.hpp"

#include "../inc/test_utils.hpp"
#include "inc/test_string.hpp"

using namespace husky;

extern std::string tmp_file_path;

typedef bool(*testcase)(); // testacse type for creation of array of function pointers

/*
 * Test getStrValue method for basic functionality
 *
 */
bool test_string_getStrValue_basic()
{
    std::cout << "* testing getStrValue method for basic functionality";

    Parser *parser = create_parser(empty_is_end);

    datatypes::String *str = new datatypes::String(parser, "foobar");

    bool retval = testStr(str->getStrValue(), "foobar");

    str->clean();
    delete str;

    cleanup_parser(parser);

    return retval;
}

/*
 * Tests copy method for basic functionality
 *
 */
bool test_string_copy_basic()
{
    std::cout << "* testing copy method for basic functionality";

    Parser *parser = create_parser(empty_is_end);

    datatypes::String *str = new datatypes::String(parser, "quuxfoobaz");

    datatypes::AbstractDataType *str_copy = str->copy();

    bool retval = testStr("quuxfoobaz", str_copy->getStrValue());

    str->clean();
    str_copy->clean();
    delete str_copy;
    delete str;

    cleanup_parser(parser);

    return retval;
}

/*
 * Tests string parse method with adding to default value
 *
 */
bool test_string_parse_with_add_val()
{
    std::cout << "* testing parse method with adding to default value";

    system(("echo \"hi'\" > " + tmp_file_path).c_str());

    Parser *parser = create_parser(empty_is_end);

    parser->line = parser->filehandler->getLine();

    parser->linei = 0;
    parser->linen = 0;

    datatypes::String *str = new datatypes::String(parser, "hello, ");

    str->parse();

    bool retval = testStr(str->getStrValue(), "hello, hi");

    str->clean();
    delete str;

    cleanup_parser(parser);

    return retval;
}

/*
 *
 *
 */
bool test_string_datatype()
{
    bool failed = false;
    int len = 3;

    testcase *funlist = (testcase*) malloc(len * sizeof(testcase));

    funlist[0] = test_string_getStrValue_basic;
    funlist[1] = test_string_copy_basic;
    funlist[2] = test_string_parse_with_add_val;

    std::cout << "| testing string datatype" << std::endl;

    for (len--; len >= 0; len--) {
        if (funlist[len]()) failed = true;
    }

    free(funlist);

    return failed;
}
