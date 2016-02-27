#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <fstream>

namespace husky {
    class FileHandler {
        private:
            std::ifstream file;

            const char *filepath;

        public:
            FileHandler (std::string);
            std::string getLine();
            char getChar();
            bool eof();
            bool is_open();
            void close();

            const char *getFilepath() { return filepath; };
    };
}

#endif
