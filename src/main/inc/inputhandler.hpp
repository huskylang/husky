#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <fstream>

namespace husky {
    class InputHandler
    {
        public:

            InputHandler(std::istream*);

            std::string getLine();

            // vars

            std::istream *inp;
    };
}

#endif
