#include <string>

#include "../inc/parser.hpp"

#include "inc/abstract.hpp"
#include "inc/number.hpp"

using namespace husky;


datatypes::Number::Number(Parser *parser, long long int value)
{
    this->value = value;
    this->parser = parser;
}


/*
 * Checks if character is numeric
 *
 */
bool datatypes::is_numeric(char ch)
{
    return ch >= 48 && ch <= 57;
}

/*
 * Parses number from line
 *
 */
void datatypes::Number::parse()
{
    int d = 1, i = this->parser->linei, i_tmp;

    for (; datatypes::is_numeric(this->parser->line[i]); i++) { }

    i--;
    i_tmp = i;

    for (; i >= this->parser->linei; i--, d *= 10) {
        this->value += d * (this->parser->line[i] - 48);
    }

    this->parser->linei = i_tmp;
}

/*
 * Creates a copy of this number
 *
 */
datatypes::AbstractDataType *datatypes::Number::copy()
{
    return new datatypes::Number(this->parser, this->value);
}
