#include <string>

#include "inc/parser.hpp"
#include "datatypes/inc/abstract.hpp"

#include "inc/function_caller.hpp"

#include "../../stdlib/inc/router.hpp"

using namespace husky;

/*
 * Throws eol error
 *
 */
void throw_eol_error(Parser *parser)
{
    parser->outhandler->error(
        "(function caller)", "unexpected eol",
        parser->line, parser->linen, parser->linei
    );
}

/*
 * Parses function call like '(cs:out 'hello')'
 *
 */
datatypes::AbstractDataType *function_caller::call(Parser *parser, std::string funname)
{
    datatypes::AbstractDataType *retval;

    int len = 0;

    datatypes::AbstractDataType **arglist;


    // // skip all spaces before funname
    //
    // while (parser->line[parser->linei] == ' ' || parser->line[parser->linei] == '\n') {
    //     if (parser->linei >= parser->line.length()) {
    //         throw_eol_error(parser);
    //         return retval;
    //     }
    //
    //     parser->linei++;
    // }
    //
    // // parse funname up to the first space
    //
    // while (parser->line[parser->linei] != ' ') {
    //     if (parser->linei >= parser->line.length()) {
    //         throw_eol_error(parser);
    //         return retval;
    //     }
    //
    //     funname += parser->line[parser->linei];
    //     parser->linei++;
    // }

    // initialize a list of arguments

    arglist = (datatypes::AbstractDataType **) malloc(
        sizeof(datatypes::AbstractDataType) * sizeof(datatypes::AbstractDataType)
    );

    // parsing arg list

    while (parser->line[parser->linei] != ')') {
        if (parser->linei >= parser->line.length()) {
            free(arglist);
            throw_eol_error(parser);
            return retval;
        }

        len++;

        // add one cell of memory to arglist

        arglist = (datatypes::AbstractDataType **) realloc(
            arglist, len * sizeof(datatypes::AbstractDataType) * sizeof(datatypes::AbstractDataType)
        );

        // skip all spaces before value

        while (parser->line[parser->linei] == ' ' || parser->line[parser->linei] == ',' || parser->line[parser->linei] == '\n') {
            parser->linei++;
        }

        arglist[len - 1] = parser->createVariable(parser->line[parser->linei]); // append to the list of arguments

        parser->linei++;
    }

    retval = stdlib::run(parser, funname, arglist, len); // run function

    // parser->outhandler->printline("funname: " + funname);

    for (len--; len >= 0; len--) {
        // parser->outhandler->printline("arg: " + arglist[len]->getStrValue());
        if (arglist[len])
            delete arglist[len];
    }

    free(arglist); // memory cleanup

    return retval;
}
