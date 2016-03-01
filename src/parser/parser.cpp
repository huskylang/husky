#include <string>

#include "datatypes/inc/abstract.hpp"
#include "inc/variable.hpp"

#include "../main/inc/outputhandler.hpp"
#include "../main/inc/inputhandler.hpp"
#include "../main/inc/filehandler.hpp"

#include "datatypes/inc/abstract.hpp"
#include "datatypes/inc/string.hpp"
#include "datatypes/inc/atom.hpp"

#include "inc/file_modifier.hpp"
#include "inc/function_caller.hpp"

#include "inc/parser.hpp"

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
 * bool (*)(char) is a function pointer
 *
 */
Parser::Parser(FileHandler *filehandler, OutputHandler *outhandler, InputHandler *inhandler, bool (*is_end)(char))
{
    this->filehandler = filehandler;

    this->outhandler = outhandler;
    this->inhandler = inhandler;

    this->is_end = is_end;
}

/*
 * Adds a variable to the scope
 *
 */
void Parser::addVariable(datatypes::AbstractDataType *var, std::string name)
{
    // add variable and increment length
    this->variables[this->variables_len++] = new Variable(var, name);
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
            // Throwing the error

            this->outhandler->error("(variables manager)", "variable: '" + name + "' has been already defined", this->line, this-> linen, this->linei);

            return true;
        }
    }

    return false;
}


/*
 * Creates and adds a variable to the scope
 *
 */
datatypes::AbstractDataType *Parser::createVariable(char ch)
{
    // variable pointer
    datatypes::AbstractDataType *var = NULL;

    std::string varname = "";

    // indentifying datatype

    if (is_var_function_call(ch)) { // is function_call or a variable
        // read varname
        for (; this->linei < this->line.length() && is_var_function_call(this->line[this->linei]); this->linei++)
        {
            varname += this->line[this->linei];
        }

        if (this->line[this->linei] == '(') { // it is a function call
            this->linei++;
            var = function_caller::call(this, varname);
        } else { // it is a variable
            this->linei--;
            var = this->getVar(varname)->getValue()->copy();
        }

        return var;

    } else if (ch == '@') { // atom
        this->linei++;
        var = new datatypes::Atom(this, "");
    } else if (ch == '\'') { // string
        this->linei++;
        var = new datatypes::String(this, "");
    } else {
        this->outhandler->error("(datatype indentifyer)", "error when indentifying datatype", this->line, this->linen, this->linei);
        return NULL;
    }

    var->parse();

    return var;
}

/*
 * Parses file up to end or to specific character (specified in function is_end)
 *
 */
void Parser::parse()
{

    datatypes::AbstractDataType *var;

    std::string varname = "";
    std::string funname = "";
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
        funname = ""; // null the funname

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
                if (this->line[this->linei] == '#') {
                    // turn on comment block
                    is_comment = true;
                    varname = ""; // null the varname
                } else if (this->line[this->linei] == '<' && this->line[this->linei + 1] == '-') {
                    this->linei++; // skip '-' character

                    if (this->checkVarname(varname)) {
                        break;
                    } else {
                        // go to the value block
                        is_varname = false;
                        is_varvalue = true;
                    }
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

                        if (var != NULL)
                            addVariable(var, varname);

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
 * Deletes all variables defined in this parser
 *
 */
void Parser::clean()
{
    for (this->variables_len--; this->variables_len >= 0; this->variables_len--) {
        this->outhandler->print(this->variables[this->variables_len]->getName()); // printing name
        this->outhandler->print(" = ");
        this->outhandler->printline(this->variables[this->variables_len]->getValue()->getStrValue()); // printing value

        delete this->variables[this->variables_len]->getValue(); // var cleanup
        delete this->variables[this->variables_len]; // delete
    }
}
