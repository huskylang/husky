#ifndef PARSER_HPP
#define PARSER_HPP

#include "variable.hpp"
// #include "../datatypes/inc/abstract.hpp"

#include "../../main/inc/outputhandler.hpp"
#include "../../main/inc/inputhandler.hpp"
#include "../../main/inc/filehandler.hpp"

namespace husky {

    /*
     * Used to parse and run a code block and create a scope
     *
     */
    class Parser
    {
        private:
            bool (*is_end)(char); // function to check if need to stop parsing

            // passports::AbstractPassport *datatypes_supported[1];
            //
            // int datatypes_supported_len = 1;

        public:
            Parser(FileHandler*, OutputHandler*, InputHandler*, bool (*)(char)); // bool (*)(char) is function pointer
            bool checkVarname(std::string);
            void parse();
            void clean();
            void error(const char *, std::string);
            void addVariable(datatypes::AbstractDataType*, std::string);
            datatypes::AbstractDataType *createVariable(char ch);
            Variable *getVar(std::string);

            // variables

            std::string line;
            int linen, linei; // used to indicate line number and line index

            OutputHandler *outhandler;
            FileHandler *filehandler;
            InputHandler *inhandler;

            Variable *variables[20]; // array of variables in this scope
            int variables_len = 0;
    };

}

#endif
