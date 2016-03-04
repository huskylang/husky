#ifndef STRINGS_HPP
#define STRINGS_HPP

#include "abstract.hpp"
#include "../../inc/parser.hpp"

namespace husky { namespace datatypes {

    class String : public AbstractDataType
    {
        private:
            husky::Parser *parser;
            std::string value;

        public:
            String(husky::Parser*, std::string);
            ~String() { };

            virtual AbstractDataType *copy();
            virtual std::string getStrValue();
            virtual void cleanup();
            virtual void parse();
    };

}}

#endif
