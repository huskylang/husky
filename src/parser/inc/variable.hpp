#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include "../datatypes/inc/abstract.hpp"

namespace husky {

    /*
     * Used to store a variable
     *
     */
    class Variable
    {
        private:
            std::string name;
            datatypes::AbstractDataType *value;

        public:
            Variable(datatypes::AbstractDataType*, std::string);

            std::string getName();
            datatypes::AbstractDataType* getValue();
    };

}

#endif
