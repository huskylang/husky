#include <string>
#include <cstring>
#include <libgen.h>

#include "inc/parser.hpp"
#include "inc/file_modifier.hpp"

// using namespace husky::file_modifier;

bool scrpt_modifier(husky::Parser*);

/*
 * Parses the modifier name
 *
 */
bool husky::file_modifier::parse(husky::Parser *parser)
{
    std::string modifier = "";

    for (; parser->linei < parser->line.length() && parser->line[parser->linei] != ' '; parser->linei++) {
        modifier += parser->line[parser->linei];
    }

    parser->linei++;

    if (modifier == "scrpt") {
        return scrpt_modifier(parser);
    } else {
        // Throw an error
        parser->outhandler->error(
            "(file modifier, parser)", \
            "unknown modifier '" + modifier + "'", \
            parser->line, parser->linen, 0
        );

        return true;
    }
}


/*
 * Finds a character in a string
 * Returns index
 *
 */
int find(char *str, char ch)
{
    int i;

    for (i = 0; i < strlen(str); i++) {
        if (str[i] == ch) {
            return i;
        }
    }

    return -1;
}

/*
 * Usage:
 * -scrpt filename
 *
 * Returns false if filename matches specified filename else true
 *
 */
bool scrpt_modifier(husky::Parser *parser)
{
    std::string _filename = ""; // filename specified in the file modifier

    int index;

    char *filename; // filename specified in the filehandler
    char *mut = strdup(parser->filehandler->getFilepath()); // create a mutable instance of filepath

    filename = basename(mut);


    // parse the _filename

    for (; parser->linei < parser->line.length(); parser->linei++) {
        if (parser->line[parser->linei] == '.') { // check if the _filename contains dots
            free(mut);

            parser->outhandler->error(
                "(file modifier, scrtp)", "specified filename contains dots", \
                parser->line, parser->linen, parser->linei
            );

            return true;
        } else {
            _filename += parser->line[parser->linei];
        }
    }

    index = find(filename, '.'); // find a first dot in the filename

    if (index != -1) {
        filename[index] = '\0'; // replace '.' with '\0'; used to extract file extension
    }

    if (strcmp(filename, _filename.c_str()) == 0) { // check filenames to match
        free(mut);

        return false;
    } else {
        free(mut);

        // throw an error
        parser->outhandler->error(
            "(file modifier, scrpt)", "filename dismatch", \
            parser->line, parser->linen, parser->linei - 1
        );

        return true;
    }
}
