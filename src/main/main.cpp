#include <string>
#include <exception>
#include <iostream>
#include <fstream>

#include "inc/argparser.hpp"
#include "inc/filehandler.hpp"
#include "inc/outputhandler.hpp"

#include "../parser/inc/parser.hpp"

using namespace husky;

// Initialization of main classes

ArgParser *argparser;
OutputHandler *outhandler;
FileHandler *filehandler;
InputHandler *inhandler;
Parser *parser;


/*
 * Parses up to end of the file
 *
 */
bool is_end(char)
{
    return false;
}

int main(int argc, char *argv[])
{
    outhandler = new OutputHandler();

    outhandler->info("(system)", "loaded output handler");

    try {
        // Initialize main classes

        argparser = new ArgParser(argc, argv); // Initilizing argparser

        outhandler->info("(system)", "parsed args");


        filehandler = new FileHandler(argparser->getFileName()); // Initializing filehandler

        outhandler->info("(system)", "loaded file");


        inhandler = new InputHandler(&std::cin);

        outhandler->info("(system)", "loaded input handler");

        // create parser

        parser = new Parser(filehandler, outhandler, inhandler, is_end); // is_end is a function

        outhandler->info("(system)", "loaded parser");

        parser->parse();

        // Memory cleanup

        filehandler->close();

        parser->clean();

        delete parser;

        delete filehandler;
        delete argparser;

        outhandler->success("(system)", "ok");

        delete outhandler;
        delete inhandler;

        return 0;
    } catch (std::string e) {
        // Catch error and print it

        outhandler->error("(critical)", e, "", 0, 0);

        // memory cleanup

        delete outhandler;
        delete inhandler;
    } catch (std::exception e) {
        // Catch system errors

        outhandler->error("(critical, system)", e.what(), "", 0, 0);

        // memory cleanup

        delete outhandler;
        delete inhandler;
    }

    return 1;
}
