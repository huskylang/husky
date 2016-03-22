#include <string>
#include "inc/function.hpp"
#include "../inc/parser.hpp"
#include "inc/abstract.hpp"
#include "inc/string.hpp"

using namespace husky::parser::datatypes;

Function::Function(husky::parser::Parser *parser)
{
    this->parser = parser_parent;
}

AbstractDataType *Function::run(AbstractDataType **arglist)
{
    return new Atom("unknown");
}
