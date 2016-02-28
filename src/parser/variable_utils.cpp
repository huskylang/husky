#include <string>

#include "inc/variable.hpp"
#include "inc/parser.hpp"

#include "inc/variable_utils.hpp"

using namespace husky;

/*
 * Finds and returns the variable in this scope
 *
 * If the variable does not exist returns NULL pointer
 *
 */
Variable *variable::getVar(Parser *parser, std::string varname)
{
    int i = 0;

    for (i = 0; i < parser->variables_len; i++) {
        if (parser->variables[i]->getName() == varname) {
            return parser->variables[i];
        }
    }

    parser->outhandler->error(
        "(variable finder)", "variable '" + varname + "' does not exist",
        parser->line, parser->linen, parser->linei
    );

    return NULL;
}
