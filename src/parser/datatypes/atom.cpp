#include <string>

#include "../inc/parser.hpp"
#include "inc/abstract.hpp"

#include "inc/atom.hpp"

using namespace husky::datatypes;


Atom::Atom(husky::Parser *parser, std::string value)
{
    this->parser = parser;
    this->value = value;
}


/*
 * Checks if character is alphabetic
 *
 */
bool is_alpha(char ch)
{
    return (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122);
}

/*
 * Parses line and gets an atom
 *
 */
void Atom::parse()
{
    while (this->parser->linei < this->parser->line.length()) {
        if (!is_alpha(this->parser->line[this->parser->linei])) {
            this->parser->linei--;
            break;
        }

        value += this->parser->line[this->parser->linei];
        this->parser->linei++;
    }
}


/*
 * Returns a copy of this atom
 *
 */
AbstractDataType *Atom::copy()
{
    return new Atom(this->parser, this->value);
}
