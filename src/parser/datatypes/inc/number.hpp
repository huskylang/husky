#ifndef NUMBER_DATATYPE_HPP
#define NUMBER_DATATYPE_HPP

namespace husky { namespace datatypes {

    bool is_numeric(char);

    class Number : public AbstractDataType
    {
        private:
            husky::Parser *parser;
            long long int value;

        public:
            Number(husky::Parser *parser, long long int number);
            ~Number() { };

            virtual AbstractDataType *copy();
            virtual void parse();

            virtual long long int getIntValue() { return this->value; };
            virtual std::string getStrValue() { return std::to_string(this->value); };
    };

}}

#endif
