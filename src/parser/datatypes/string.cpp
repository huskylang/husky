#include <string>
#include "inc/string.hpp"
#include "inc/abstract.hpp"
#include "../inc/parser.hpp"

using namespace husky::datatypes;

String::String(husky::Parser *parser, std::string value)
{
    this->parser = parser;
    this->value = value;
}

/*
 * Copy Method
 *
 */
AbstractDataType *String::copy()
{
    return new String(this->parser, this->value);
}

/*
 * Parses variable value up to "'"
 *
 */
void String::parse()
{
    char ch;

    // this->parser->outhandler->printline(std::to_string(this->parser->linen) + " " + std::to_string(this->parser->linei));

    for (; this->parser->linei < this->parser->line.length(); this->parser->linei++) {
        ch = this->parser->line[this->parser->linei];

        if (ch == '\'') {
            break;
        } else if (this->parser->linei == this->parser->line.length() - 1) {
            // Throwing eol error
            this->parser->outhandler->error("(string)", "unexpected eol", this->parser->line, this->parser->linen, this->parser->linei);

            return;
        }

        this->value += ch;
    }
}

void String::cleanup()
{

}

/**
 ** Getters
 **
 **/

std::string String::getStrValue()
{
    return this->value;
}
