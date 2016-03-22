#include <string>

#include "inc/parser.hpp"

#include "datatypes/inc/abstract.hpp"
#include "datatypes/inc/atom.hpp"

#include "inc/function_caller.hpp"

#include "../stdlib/inc/module_function.hpp"
#include "../stdlib/inc/module.hpp"
#include "../stdlib/inc/stdlib.hpp"

using namespace husky;

extern int modules_len;
extern lib::Module **modules;

/*
 * Throws eol error
 *
 */
void throw_eol_error(Parser *parser)
{
    parser->error("(function caller)", "unexpected eol");
}


/*
 * Runs module function
 *
 */
datatypes::AbstractDataType *run_module(Parser *parser, std::string funname, datatypes::AbstractDataType **arglist, int len)
{
    int i;
    lib::Module *module = NULL;
    lib::ModFunction *function = NULL;

    // parser modname and funname from full funname

    std::size_t pos = funname.find(":");

    std::string modname = funname.substr(0, pos);

    funname = funname.substr(pos + 1);

    // find module

    for (i = 0; i < modules_len; i++) {
        if (modname == modules[i]->getName()) {
            module = modules[i];
            break;
        }
    }

    if (module) {
        // find function

        for (i = 0; i < module->getFunsLen(); i++) {
            if(funname == module->getFuns()[i]->getName()) {
                function = module->getFuns()[i];
                break;
            }
        }

        if (function) {
            return function->run(parser, arglist, len);
        } else {
            parser->error("(module manager)", "in module '" + modname + "' there is no function '" + funname + "'");
            return new datatypes::Atom(parser, "bad");
        }
    } else {
        parser->error("(module manager)", "there is no module named '" + modname + "'");
        return new datatypes::Atom(parser, "bad");
    }
}

/*
 * Parses function call like 'cs:out('hello')'
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

    retval = run_module(parser, funname, arglist, len); // run function
    // retval = stdlib::run(parser, funname, arglist, len); // run function

    // parser->outhandler->printline("funname: " + funname);

    for (len--; len >= 0; len--) {
        // parser->outhandler->printline("arg: " + arglist[len]->getStrValue());
        if (arglist[len])
            delete arglist[len];
    }

    free(arglist); // memory cleanup

    return retval;
}
