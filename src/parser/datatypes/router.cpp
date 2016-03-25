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

std::string varname = "";

/*
 * Checks if this character is supported in variables and function calls
 *
 */
bool is_var_function_call(char ch)
{
    //      big alpha                 small alpa
    return (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch == ':') || (ch == '_');
}


/*
 * Identifies datatype and returns a ready variable
 *
 */
datatypes::AbstractDataType *datatypes::router(Parser *parser, char ch, bool throw_error)
{
    // variables pointers
    Variable *varhold;
    datatypes::AbstractDataType *var = NULL;

    varname = "";

    // indentifying datatype

    if (is_var_function_call(ch)) { // is function_call or a variable
        // read varname
        for (;
            parser->linei < parser->line.length()
                && (
                    is_var_function_call(parser->line[parser->linei])
                    || datatypes::is_numeric(parser->line[parser->linei])
                );
            parser->linei++
        )
        {
            varname += parser->line[parser->linei];
        }

        if (parser->line[parser->linei] == '(') { // it is a function call
            parser->linei++;
            var = function_caller::call(parser, varname);
        } else { // it is a variable
            varhold = parser->getVar(varname, throw_error);

            parser->linei--;

            if (!varhold && throw_error)
                var = new datatypes::String(parser, "");
            else if (varhold)
                var = varhold->getValue()->copy();
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
        parser->error("(datatype indentifyer)", "error when indentifying datatype");
        return new datatypes::String(parser, "");
    }

    var->parse();

    return var;
}
