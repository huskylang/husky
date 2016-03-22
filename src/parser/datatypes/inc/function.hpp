#ifndef PARSER_HPP
#define PARSER_HPP

namespace husky::parser::datatypes {

    class Function : public AbstractDataType
    {
        private:
            husky::parser::Parser *parser;

        public:
            Function(husky::parser::Parser*);

            virtual AbstractDataType *run(AbstractDataType**);
    };

}

#endif
