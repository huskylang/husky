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

using namespace husky;

extern std::string varname;

int modules_len;
lib::Module **modules;

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

    // this->modules = malloc(sizeof(lib::Module) * this->modules_len);

    modules = stdlib::modlist();
    modules_len = stdlib::modlist_len();
}

/*
 *
 *
 */
inline void Parser::skipSpaces()
{
    for (;
        this->linei < this->line.length() && this->line[this->linei] == ' ';
        this->linei++
    );
}

/*
 * Checks two variables for equality
 *
 */
bool Parser::patternMatch(
    datatypes::AbstractDataType *var1, datatypes::AbstractDataType *var2, bool throw_error
)
{
    if (var1->getStrValue() != var2->getStrValue()) {
        if (throw_error)
            this->error("(variables manager)", "pattern match failed");

        return false;
    }

    return true;
}

/*
 * Adds a variable to the scope
 *
 */
bool Parser::addVariable(datatypes::AbstractDataType *var, std::string name, bool throw_error)
{
    bool retval = true;

    if (name[0] == '_') {
        //
    } else if (this->checkVarname(name)) {
        retval = this->patternMatch(var, this->getVar(name, true)->getValue(), throw_error);

        delete var; // deleting variable because we do not need it. we have its copy
    } else {
        // add variable and increment length
        this->variables[this->variables_len++] = new Variable(var, name);
    }

    return retval;
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
datatypes::AbstractDataType *Parser::createVariable(char ch, bool throw_error)
{
    return datatypes::router(this, ch, throw_error);
}

/*
 * Parses file up to end or to specific character (specified in function is_end)
 *
 */
void Parser::parse()
{
    datatypes::AbstractDataType *var;
    datatypes::AbstractDataType *var1;

    std::string varname_dump;

    // blocks declarations
    bool is_leftside;
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

        is_leftside = true;
        this->linei = 0;

        var = NULL;

        this->skipSpaces();

        this->linestart = this->linei;

        if (this->line[this->linei] == '-') { // file modifier
           // Parse file modifier
           this->linei++; // skip '-' character
           this->linestart = this->linei;

           is_error = file_modifier::parse(this); // set the criticall error to true
        } else {
            for (; this->linei < this->line.length(); this->linei++) {

                // check if eof or end character
                if (is_end(this->line[this->linei])) {
                    break;
                } else if (this->line[this->linei] == ';') {
                    break;
                } else if (
                    this->line[this->linei] == '<'
                    && this->line[this->linei + 1] == '-'
                    && is_leftside
                ) {
                    // go to the value block
                    is_leftside = false;
                    this->linei += 2;
                } else if (is_leftside && this->line[this->linei] != ' ') {
                    var = this->createVariable(this->line[this->linei], false);

                    // this->linei++;
                    this->skipSpaces();
                } else if (this->line[this->linei] != ' ') {
                    if (!var) {
                        varname_dump = varname;
                        var = this->createVariable(this->line[this->linei], true);

                        this->addVariable(var, varname_dump, true);
                    } else {
                        var1 = this->createVariable(this->line[this->linei], true);

                        this->patternMatch(var, var1, true);
                        
                        delete var;
                        delete var1;
                    }
                }
            }

            if (is_leftside && var) {
                delete var;
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
