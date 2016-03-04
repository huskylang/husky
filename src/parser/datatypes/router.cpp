#include <string>

#include "../inc/parser.hpp"
#include "../inc/function_caller.hpp"

#include "inc/abstract.hpp"

#include "inc/string.hpp"
#include "inc/atom.hpp"
#include "inc/number.hpp"
// #include "inc/function.hpp"

#include "inc/router.hpp"

using namespace husky;


/*
 * Checks if this character is supported in variables and function calls
 *
 */
bool is_var_function_call(char ch)
{
    return (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch == ':');
}


/*
 * Identifies datatype and returns a ready variable
 *
 */
datatypes::AbstractDataType *datatypes::router(Parser *parser, char ch)
{
    // variable pointer
    datatypes::AbstractDataType *var = NULL;

    std::string varname = "";

    // indentifying datatype

    if (is_var_function_call(ch)) { // is function_call or a variable
        // read varname
        for (; parser->linei < parser->line.length() && (is_var_function_call(parser->line[parser->linei]) || datatypes::is_numeric(parser->line[parser->linei])); parser->linei++)
        {
            varname += parser->line[parser->linei];
        }

        if (parser->line[parser->linei] == '(') { // it is a function call
            parser->linei++;
            var = function_caller::call(parser, varname);
        } else { // it is a variable
            parser->linei--;
            var = parser->getVar(varname)->getValue()->copy();
        }

        return var;

    } else if (ch == '@') { // atom
        parser->linei++;
        var = new datatypes::Atom(parser, "");
    } else if (ch == '\'') { // string
        parser->linei++;
        var = new datatypes::String(parser, "");
    } else if (datatypes::is_numeric(ch)) { // number
        var = new datatypes::Number(parser, 0);
    } else { // error
        parser->outhandler->error("(datatype indentifyer)", "error when indentifying datatype", parser->line, parser->linen, parser->linei);
        return NULL;
    }

    var->parse();

    return var;
}
