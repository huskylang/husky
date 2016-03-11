#ifndef OUTPUTHANDLER_HPP
#define OUTPUTHANDLER_HPP

#include <iostream>

namespace husky {
    class OutputHandler {
        private:
            const std::string red = "0;31";
            const std::string blue = "0;33";
            const std::string green = "0;32";

            std::ostream *stream;

        public:
            OutputHandler(std::ostream *);
            void print(std::string);
            void printline(std::string);
            void printchar(char);

            void error(const char *sect, std::string, std::string, int, int);
            void info(const char *sect, std::string);
            void success(const char *sect, std::string);
    };
}

#endif
