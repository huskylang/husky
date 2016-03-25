#ifndef PARSER_HPP
#define PARSER_HPP

#include "variable.hpp"
// #include "../datatypes/inc/abstract.hpp"

#include "../../main/inc/outputhandler.hpp"
#include "../../main/inc/inputhandler.hpp"
#include "../../main/inc/filehandler.hpp"

// #include "../../stdlib/inc/module.hpp"

namespace husky {

    /*
     * Used to parse and run a code block and create a scope
     *
     */
    class Parser
    {
        private:
            bool (*is_end)(char); // function to check if need to stop parsing

        public:
            Parser(FileHandler*, OutputHandler*, InputHandler*, bool (*)(char)); // bool (*)(char) is function pointer

            bool checkVarname(std::string);
            bool addVariable(datatypes::AbstractDataType*, std::string, bool);

            bool patternMatch(datatypes::AbstractDataType *, datatypes::AbstractDataType *, bool);

            inline void skipSpaces();

            void parse();
            void clean();
            void error(const char *, std::string);

            datatypes::AbstractDataType *createVariable(char, bool);
            Variable *getVar(std::string, bool);

            // variables

            std::string line;
            int linen, linei; // used to indicate line number and line index

            int linestart;

            OutputHandler *outhandler;
            FileHandler *filehandler;
            InputHandler *inhandler;

            Variable *variables[20]; // array of variables in this scope
            int variables_len = 0;

            // lib::Module **modules; // array of modules in this scope
            // int modules_len;
    };

}

#endif
