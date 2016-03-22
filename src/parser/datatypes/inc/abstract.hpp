#ifndef ABSTRACT_DATATYPE_HPP
#define ABSTRACT_DATATYPE_HPP


namespace husky { namespace datatypes {

    /*
     * Abstract data type class
     * used for creation lists of variables
     *
     */
    class AbstractDataType
    {
        public:
            virtual ~AbstractDataType() { };
            virtual void parse() = 0;
            virtual AbstractDataType *copy() = 0;
            virtual void clean() {};
            virtual std::string getStrValue() { return ""; };
            virtual long long int getIntValue() { return 0; };
            virtual AbstractDataType *run(AbstractDataType **arglist) { return NULL; };
    };

}}

#endif
