#include <string>
#include <iostream>
#include "inc/outputhandler.hpp"

using namespace husky;


OutputHandler::OutputHandler(std::ostream *stream)
{
    this->stream = stream;
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
 * Prints msg using red color to console
 *
 */
void OutputHandler::error(std::string msg)
{
    this->stream = &std::cerr;

    printline("\e[" + red + "m" + msg + "\e[0m");

    this->stream = &std::cout;
}


/*
 * Prints info to console
 *
 */
void OutputHandler::info(std::string msg)
{
    printline("\e[" + blue + "m" + "[i] " + msg + "\e[0m");
}


/*
 * Prints success message to console
 *
 */
void OutputHandler::success(std::string msg)
{
    printline("\e[" + green + "m" + "[s] " + msg + "\e[0m");
}
