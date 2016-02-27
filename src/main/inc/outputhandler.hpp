#ifndef OUTPUTHANDLER_HPP
#define OUTPUTHANDLER_HPP

namespace husky {
    class OutputHandler {
        private:
            const std::string red = "0;31";
            const std::string blue = "0;33";
            const std::string green = "0;32";

        public:
            OutputHandler();
            void print(std::string);
            void printline(std::string);
            void printchar(char);

            void error(const char *sect, std::string, std::string, int, int);
            void info(const char *sect, std::string);
            void success(const char *sect, std::string);
    };
}

#endif
