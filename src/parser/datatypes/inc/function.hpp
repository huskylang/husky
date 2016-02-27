#ifndef PARSER_HPP
#define PARSER_HPP

namespace husky::parser::datatypes {

    class Function : public AbstractDataType
    {
        private:
            husky::parser::Parser *parser;

            AbstractDataType *variables[20];
            int variables_len = 0;

            std::string name;

        public:
            Function(husky::parser::Parser*, std::string);

            virtual std::string getName();

            int run(AbstractDataType**);
    };

}

#endif
