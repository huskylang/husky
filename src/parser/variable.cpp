#include <string>
#include "datatypes/inc/abstract.hpp"
#include "inc/variable.hpp"

using namespace husky;


Variable::Variable(datatypes::AbstractDataType *value, std::string name)
{
    this->name = name;
    this->value = value;
}

/**
 ** Getters
 **
 **/

std::string Variable::getName()
{
    return name;
}

datatypes::AbstractDataType* Variable::getValue()
{
    return value;
}
