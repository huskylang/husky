#include <string>
#include "inc/function.hpp"
#include "../inc/parser.hpp"
#include "inc/abstract.hpp"
#include "inc/string.hpp"

using namespace husky::parser::datatypes;

Function::Function(husky::parser::Parser *parser_parent, std::string name_parent)
{
    name = name_parent;
    parser = parser_parent;
}

std::string Function::getName()
{
    return name;
}

int Function::run(AbstractDataType *arglist[])
{
    char ch;

    while (!filehandler->eof()) {
        ch = parser->filehandler->getChar()

        if (ch == '.') {
            break;
        }

        parser->outhandler->print();

    }

    return 0;
}
