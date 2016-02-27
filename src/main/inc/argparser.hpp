#ifndef ARGPARSER_HPP
#define ARGPARSER_HPP

namespace husky {
    class ArgParser {
        private:
            std::string cmdname;
            std::string filename;

        public:
            ArgParser (int, char**);
            std::string getFileName();
            std::string getCmdName();
    };
}

#endif
