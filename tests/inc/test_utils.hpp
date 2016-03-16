#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>

#include "../../src/main/inc/filehandler.hpp"
#include "../../src/main/inc/outputhandler.hpp"
#include "../../src/main/inc/inputhandler.hpp"

#include "../../src/parser/inc/parser.hpp"

bool testOutput(std::string, std::string);
bool testStr(std::string, std::string);
bool testInt(long long int, long long int);
bool testChar(char, const char);
bool testBool(bool, bool);

bool empty_is_end(char);

husky::Parser *create_parser(bool (*)(char));

void cleanup_parser(husky::Parser *parser);

husky::FileHandler *create_filehandler();
husky::InputHandler *create_inhandler();
husky::OutputHandler *create_outhandler();

#endif
