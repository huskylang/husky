#include <string>
#include <exception>
#include <iostream>

#include "inc/argparser.hpp"
#include "inc/filehandler.hpp"
#include "inc/outputhandler.hpp"

#include "../parser/inc/parser.hpp"

using namespace husky;

// Initialization of main classes

ArgParser *argparser;
OutputHandler *outhandler;
FileHandler *filehandler;
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

    try {
        // Initialize main classes

        argparser = new ArgParser(argc, argv); // Initilizing argparser

        outhandler->info("(system)", "parsed args");


        filehandler = new FileHandler(argparser->getFileName()); // Initializing filehandler

        outhandler->info("(system)", "loaded file");


        // create parser

        parser = new Parser(filehandler, outhandler, is_end); // is_end is a function

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

        return 0;
    } catch (std::string e) {
        // Catch error and print it

        outhandler->error("(critical)", e, "", 0, 0);

        delete outhandler; // memory cleanup
    } catch (std::exception e) {
        // Catch system errors

        outhandler->error("(critical, system)", e.what(), "", 0, 0);

        delete outhandler; // memory cleanup
    }

    return 1;
}
