#include "abstract.hpp"
#include "../datatypes/inc/string.hpp";
#include "string.hpp"

using namespace husky::passports;

/**
 ** Getters
 **
 **/

char StringPassport::getStart()
{
    return start;
}

husky::datatypes::String StringPassport::getStringtype()
{
    return stringtype;
}
