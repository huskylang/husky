#include <string>
#include <iostream>
#include <cstdlib>

#include "../../src/parser/inc/parser.hpp"

#include "../../src/parser/datatypes/inc/atom.hpp"
#include "../../src/parser/datatypes/inc/abstract.hpp"

#include "../inc/test_utils.hpp"
#include "inc/test_atom.hpp"

using namespace husky;

extern std::string tmp_file_path;

typedef bool(*testcase)(); // testcase type for creation of array of function pointers

/*
 * Test getStrValue method for basic functionality
 *
 */
bool test_atom_getStrValue_basic()
{
    std::cout << "* testing getStrValue method for basic functionality";

    Parser *parser = create_parser(empty_is_end);

    datatypes::Atom *atom = new datatypes::Atom(parser, "foobar");

    bool retval = testStr(atom->getStrValue(), "foobar");

    atom->clean();
    delete atom;

    cleanup_parser(parser);

    return retval;
}

/*
 * Tests copy method for basic functionality
 *
 */
bool test_atom_copy_basic()
{
    std::cout << "* testing copy method for basic functionality";

    Parser *parser = create_parser(empty_is_end);

    datatypes::Atom *atom = new datatypes::Atom(parser, "quuxfoobaz");

    datatypes::AbstractDataType *atom_copy = atom->copy();

    bool retval = testStr("quuxfoobaz", atom_copy->getStrValue());

    atom->clean();
    atom_copy->clean();
    delete atom_copy;
    delete atom;

    cleanup_parser(parser);

    return retval;
}

/*
 * Tests atom parse method with adding to default value
 *
 */
bool test_atom_parse_with_add_val()
{
    std::cout << "* testing parse method with adding to default value";

    system(("echo \"hi foo\" > " + tmp_file_path).c_str());

    Parser *parser = create_parser(empty_is_end);

    parser->line = parser->filehandler->getLine();

    parser->linei = 0;
    parser->linen = 0;

    datatypes::Atom *atom = new datatypes::Atom(parser, "hello");

    atom->parse();

    bool retval = testStr(atom->getStrValue(), "hellohi");

    atom->clean();
    delete atom;

    cleanup_parser(parser);

    return retval;
}

/*
 *
 *
 */
bool test_atom_datatype()
{
    bool failed = false;
    int len = 3;

    testcase *funlist = (testcase*) malloc(len * sizeof(testcase));

    funlist[0] = test_atom_getStrValue_basic;
    funlist[1] = test_atom_copy_basic;
    funlist[2] = test_atom_parse_with_add_val;

    std::cout << "| testing atom datatype" << std::endl;

    for (len--; len >= 0; len--) {
        if (funlist[len]()) failed = true;
    }

    free(funlist);

    return failed;
}
