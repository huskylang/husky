#include <string>
#include <cstdlib>

#include "datatypes/inc/abstract.hpp"
#include "inc/variable.hpp"

#include "../main/inc/outputhandler.hpp"
#include "../main/inc/inputhandler.hpp"
#include "../main/inc/filehandler.hpp"

#include "datatypes/inc/router.hpp"

#include "inc/file_modifier.hpp"
#include "inc/function_caller.hpp"

#include "../stdlib/inc/module.hpp"
#include "../stdlib/inc/stdlib.hpp"

#include "inc/parser.hpp"

int modules_len;
lib::Module **modules;

using namespace husky;

/*
 * bool (*)(char) is a function pointer
 *
 */
Parser::Parser(FileHandler *filehandler, OutputHandler *outhandler, InputHandler *inhandler, bool (*is_end)(char))
{
    this->filehandler = filehandler;

    this->outhandler = outhandler;
    this->inhandler = inhandler;

    this->is_end = is_end;

    modules_len = stdlib::modlist_len();

    // this->modules = malloc(sizeof(lib::Module) * this->modules_len);
    modules = stdlib::modlist();
}

/*
 * Adds a variable to the scope
 *
 */
bool Parser::addVariable(datatypes::AbstractDataType *var, std::string name, bool is_custom)
{
    if (this->checkVarname(name)) {
        if (var->getStrValue() != this->getVar(name)->getValue()->getStrValue()) {
            this->error("(variables manager)", "pattern match failed");
        }

        delete var; // deleting variable because we do not need it. we have its copy
    } else {
        // add variable and increment length
        this->variables[this->variables_len++] = new Variable(var, name);
    }
}

/*
 * Checks if this variable name is unique
 *
 */
bool Parser::checkVarname(std::string name)
{
    int i;

    // Check if there is another variable with this name

    for (i = 0; i < this->variables_len; i++) {
        if (this->variables[i]->getName() == name) {
            return true;
        }
    }

    return false;
}


/*
 * Creates a variable
 *
 */
datatypes::AbstractDataType *Parser::createVariable(char ch)
{
    return datatypes::router(this, ch);
}

/*
 * Parses file up to end or to specific character (specified in function is_end)
 *
 */
void Parser::parse()
{

    datatypes::AbstractDataType *var;

    std::string varname = "";
    // std::string funname = "";
    std::string line;

    // blocks declarations
    bool is_comment;
    bool is_varname;
    bool is_varvalue;
    bool is_error = false;

    // parse content

    for (this->linen = 0; ; this->linen++) {
        if (is_error) { // if it is a criticall error
            break;
        }

        this->line = this->filehandler->getLine();

        if (this->filehandler->eof()) {
            break;
        }

        is_comment = false;
        is_varname = true;
        is_varvalue = false;

        varname = ""; // null the varname
        // funname = ""; // null the funname

        for (this->linei = 0; this->linei < this->line.length(); this->linei++) {

            // check if eof or end character
            if (is_end(this->line[this->linei])) {
                break;
            }

            if (is_comment) {
                if (this->line[this->linei] == '\n') {
                    // go to the next line
                    is_comment = false;

                    is_varname = true;
                    is_varvalue = false;
                }
            } else {
                if (this->line[this->linei] == ';') {
                    // turn on comment block
                    is_comment = true;
                    varname = ""; // null the varname
                } else if (this->line[this->linei] == '<' && this->line[this->linei + 1] == '-') {
                    this->linei++; // skip '-' character
                    // go to the value block
                    is_varname = false;
                    is_varvalue = true;
                } else if (this->line[this->linei] == '(') {
                    this->linei++; // skip '(' character
                    var = function_caller::call(this, varname);

                    if (!is_varvalue) { // if function retval is not used
                        delete var; // deleting var
                    }
                } else if (this->line[this->linei] == '-') {
                    // Parse file modifier
                    this->linei++; // skip '-' character
                    is_error = file_modifier::parse(this); // set the criticall error to true
                } else if (this->line[this->linei] != ' ') {
                    if (is_varname) {
                        varname += this->line[this->linei]; // add character to varname
                    } else if (is_varvalue) {
                        // create and add variable
                        var = createVariable(this->line[this->linei]);

                        if (var != NULL) // check if there are any errors
                            addVariable(var, varname, true);

                        varname = true;
                        is_varvalue = false;
                        varname = ""; // null the varname
                    }
                }
            }
        }
    }
}


/*
 * Prints error to console
 *
 * Usage:
 * parser->error("(test section)", "hello error");
 *
 */
void Parser::error(const char *sect, std::string msg)
{
    int i = this->linei;

    this->outhandler->stream = &std::cerr;

    this->outhandler->error(sect + (" " + msg));

    this->outhandler->print("       ");
    this->outhandler->printline("" \
        + this->line \
        + "  [" \
        + std::to_string(this->linen + 1) + ":" + std::to_string(this->linei + 1) \
        + "]"
    );
    this->outhandler->print("       ");

    for (; i > 0; i--) {
        this->outhandler->print(" ");
    }

    this->outhandler->printline("^");

    this->outhandler->stream = &std::cout;
}


/*
 * Deletes all variables defined in this parser
 *
 */
void Parser::clean()
{
    int funs_len;

    for (this->variables_len--; this->variables_len >= 0; this->variables_len--) {
#ifdef VERBOSE_PRINTING
        this->outhandler->print(this->variables[this->variables_len]->getName()); // printing name
        this->outhandler->print(" = ");
        this->outhandler->printline(this->variables[this->variables_len]->getValue()->getStrValue()); // printing value
#endif

        delete this->variables[this->variables_len]->getValue(); // var cleanup
        delete this->variables[this->variables_len]; // delete
    }

    for (modules_len--; modules_len >= 0; modules_len--) {
        funs_len = modules[modules_len]->getFunsLen();

        for (funs_len--; funs_len >= 0; funs_len--) {
            delete modules[modules_len]->getFuns()[funs_len];
        }

        free(modules[modules_len]->getFuns());

        delete modules[modules_len];
    }

    free(modules);
}
