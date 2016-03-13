#ifndef OUTPUTHANDLER_HPP
#define OUTPUTHANDLER_HPP

#include <iostream>

namespace husky {
    class OutputHandler {
        private:
            const std::string red = "0;31";
            const std::string blue = "0;33";
            const std::string green = "0;32";

        public:
            OutputHandler(std::ostream *);
            void print(std::string);
            void printline(std::string);
            void printchar(char);

            void error(std::string);
            void info(std::string);
            void success(std::string);

            std::ostream *stream;
    };
}

#endif
