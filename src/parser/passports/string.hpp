#ifndef STRING_PASSPORT_HPP
#define STRING_PASSPORT_HPP

#include "../datatypes/inc/string.hpp"

namespace husky { namespace passports {

    /*
     * String Data Type Indentifier
     *
     */
    class StringPassport : public AbstractPassport
    {
        public:
            husky::datatypes::String stringtype;
            char start = '\'';

        public:
            StringPassport();
            char getStart();
            husky::datatypes::String getStringtype();
    };

}}

#endif
