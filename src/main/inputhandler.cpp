#include <string>
#include <fstream>

#include "inc/inputhandler.hpp"

using namespace husky;

/*
 * @param inp, can be std::cin or an opened file
 *
 */
InputHandler::InputHandler(std::istream *inp)
{
    this->inp = inp;
}

/*
 * Gets a line from the stdins
 *
 */
std::string InputHandler::getLine()
{
    std::string line;

    std::getline((*this->inp), line);

    return line;
}
