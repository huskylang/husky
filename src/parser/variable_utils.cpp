#include <string>

#include "inc/variable.hpp"
#include "inc/parser.hpp"

using namespace husky;

/*
 * Finds and returns the variable in this scope
 *
 * If the variable does not exist returns NULL pointer
 *
 */
Variable *Parser::getVar(std::string varname)
{
    int i = 0;

    for (i = 0; i < this->variables_len; i++) {
        if (this->variables[i]->getName() == varname) {
            return this->variables[i];
        }
    }

    this->error(
        "(variable finder)", "variable '" + varname + "' does not exist"
    );

    return NULL;
}
