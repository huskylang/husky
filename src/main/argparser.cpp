#include <string>
#include "inc/argparser.hpp"

#define ARGC 2

using namespace husky;

ArgParser::ArgParser(int argc, char *argv[])
{
    if (argc < ARGC) {
        throw std::string("not enough arguments");
    } else {
        this->cmdname = argv[0];
        this->filename = argv[1];
    }
}

/**
 ** Getters
 **/

std::string ArgParser::getFileName()
{
    return this->filename;
}

std::string ArgParser::getCmdName()
{
    return this->cmdname;
}
