#ifndef ATOM_DATATYPE_HPP
#define ATOM_DATATYPE_HPP

namespace husky { namespace datatypes {

    class Atom : public AbstractDataType
    {
        private:
            husky::Parser *parser;
            std::string value;

        public:
            Atom(husky::Parser *, std::string);
            ~Atom() { };

            virtual bool compare(AbstractDataType*);

            virtual void parse();
            virtual std::string getStrValue() { return this->value; };
            virtual AbstractDataType *copy();
    };

}}

#endif
