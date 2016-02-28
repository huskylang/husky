#ifndef STRINGS_HPP
#define STRINGS_HPP

#include "abstract.hpp"
#include "../../inc/parser.hpp"

namespace husky { namespace datatypes {

    class String : public AbstractDataType
    {
        private:
            std::string value;
            husky::Parser *parser;

        public:
            String(husky::Parser*, std::string);
            ~String() { };
            virtual std::string getStrValue();
            virtual void cleanup();
            virtual void parse();
    };

}}

#endif
