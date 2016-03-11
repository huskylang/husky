#include <string>
#include <exception>
#include <iostream>
#include <fstream>

#include "inc/argparser.hpp"
#include "inc/filehandler.hpp"
#include "inc/outputhandler.hpp"

#include "../parser/inc/parser.hpp"

/* Uncomment to enable verbose printing */
// #define VERBOSE_PRINTING

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
    outhandler = new OutputHandler(&std::cout);

#ifdef VERBOSE_PRINTING
    outhandler->info("(system)", "loaded output handler");
#endif

    try {
        // Initialize main classes

        argparser = new ArgParser(argc, argv); // Initilizing argparser

#ifdef VERBOSE_PRINTING
        outhandler->info("(system)", "parsed args");
#endif

        filehandler = new FileHandler(argparser->getFileName()); // Initializing filehandler

#ifdef VERBOSE_PRINTING
        outhandler->info("(system)", "loaded file");
#endif

        inhandler = new InputHandler(&std::cin);

#ifdef VERBOSE_PRINTING
        outhandler->info("(system)", "loaded input handler");
#endif

        // create parser

        parser = new Parser(filehandler, outhandler, inhandler, is_end); // is_end is a function

#ifdef VERBOSE_PRINTING
        outhandler->info("(system)", "loaded parser");
#endif

        parser->parse();

        // Memory cleanup

        filehandler->close();

        parser->clean();

        delete parser;

        delete filehandler;
        delete argparser;

#ifdef VERBOSE_PRINTING
        outhandler->success("(system)", "ok");
#endif

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
