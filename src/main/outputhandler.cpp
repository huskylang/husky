#include <string>
#include <iostream>
#include "inc/outputhandler.hpp"

using namespace husky;


OutputHandler::OutputHandler()
{
    //
}

/*
 * Prints message to console
 *
 */
void OutputHandler::print(std::string msg)
{
    (*this->stream) << msg;
}


/*
 * Prints message with endline character
 *
 */
void OutputHandler::printline(std::string msg)
{
    (*this->stream) << msg << std::endl;
}

/*
 * Prints character to console
 *
 */
void OutputHandler::printchar(char ch)
{
    (*this->stream) << ch;
}

/*
 * Prints error to console
 *
 * Usage:
 * outputhandler->error("(test section)", "hello error", parser->line, parser->linen, parser->linei);
 *
 */
void OutputHandler::error(const char *sect, std::string msg, std::string line, int il, int ic)
{
    this->stream = &std::cerr;

    printline("\e[" + red + "m" + "[e] " + sect + " " + msg + "\e[0m");

    this->print("       ");
    this->printline(line + "  [" + std::to_string(il + 1) + ":" + std::to_string(ic + 1) + "]");
    this->print("       ");

    for (; ic > 0; ic--) {
        this->print(" ");
    }

    this->printline("^");

    this->stream = &std::cout;
}


/*
 * Prints info to console
 *
 */
void OutputHandler::info(const char *sect, std::string msg)
{
    printline("\e[" + blue + "m" + "[i] " + sect + " " + msg + "\e[0m");
}


/*
 * Prints success message to console
 *
 */
void OutputHandler::success(const char *sect, std::string msg)
{
    printline("\e[" + green + "m" + "[s] " + sect + " " + msg + "\e[0m");
}
