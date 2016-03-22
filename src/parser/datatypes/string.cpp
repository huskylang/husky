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

    for (; this->parser->linei < this->parser->line.length(); this->parser->linei++) {
        ch = this->parser->line[this->parser->linei];

        if (ch == '\'') {
            break;
        } else if (this->parser->linei == this->parser->line.length() - 1) {
            // Throwing eol error
            this->parser->error("(string)", "unexpected eol");

            return;
        } else if (ch == '\\') {
            ch = this->parser->line[++this->parser->linei];

            switch (ch) {
                case '\'':
                    ch = '\'';
                    break;
                case 't':
                    ch = '\t';
                    break;
                case 'n':
                    ch = '\n';
                    break;
                case 'r':
                    ch = '\r';
                    break;
                case 'v':
                    ch = '\v';
                    break;
                case '\\':
                    ch = '\\';
                    break;
                default:
                    this->parser->error("(string)", std::string("'\\") + ch + "' is not known escape character");
                    ch = '\\';
                    this->parser->linei--;
            }
        }

        this->value += ch;
    }
}


/**
 ** Getters
 **
 **/

std::string String::getStrValue()
{
    return this->value;
}
