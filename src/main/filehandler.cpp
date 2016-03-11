#include <iostream>
#include <string>
#include "inc/filehandler.hpp"

using namespace husky;


FileHandler::FileHandler(std::string filename)
{
    this->file.open(filename, std::ios::in); // open file in input mode

    if (!is_open()) {
        throw "file: '" + filename + "' not found"; // throw file not found error
    }

    this->filepath = filename.c_str();
}


/*
 * Gets a line from the file
 *
 */
std::string FileHandler::getLine()
{
    std::string line;

    std::getline(this->file, line);

    return line;
}


/*
 * Gets a character from the file
 *
 */
char FileHandler::getChar()
{
    return this->file.get();
}


/*
 * Returns true if eof else false
 *
 */
bool FileHandler::eof()
{
    return this->file.eof();
}

/*
 * Returns true if file is open else false
 *
 */
bool FileHandler::is_open()
{
    return this->file.is_open();
}

/*
 * Close file
 *
 */
void FileHandler::close()
{
    this->file.close();
}
