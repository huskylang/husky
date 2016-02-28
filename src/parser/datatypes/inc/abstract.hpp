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
            virtual void cleanup() {};
            virtual std::string getStrValue() {return "";};
            virtual int getIntValue() {return 0;};
    };

}}

#endif
