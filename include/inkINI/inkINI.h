#ifndef INK_INI_H
#define INK_INI_H

#include <stdio.h>

/*** Default values for macros ***/

#ifndef INKINI_COMMENT
#   define INKINI_COMMENT '#'
#endif

#ifndef INKINI_MAX_LINE_LENGTH
#   define INKINI_MAX_LINE_LENGTH 80
#endif

#ifndef INKINI_MAX_VALUES
#   define INKINI_MAX_VALUES 32
#endif

#ifndef INKINI_MAX_ENTRY_LENGTH
#   define INKINI_MAX_ENTRY_LENGTH 32
#endif

#ifndef INKINI_MAX_SECTIONS
#   define INKINI_MAX_SECTIONS 8
#endif

struct entry {
    char key[INKINI_MAX_ENTRY_LENGTH];
    char value[INKINI_MAX_ENTRY_LENGTH];
    int  seciton;
};

struct inkINI_file {
    FILE*         file;
    struct entry* entries;
};

typedef struct inkINI_file inkINI_file;

/**
 * Opens a given .ini file
 *
 * Will create a new .ini file if filename does not exist.
 * Expects that filename is the name of a .ini file.
 */
inkINI_file inkINI_load_file(char* filename);

/**
 * Closes a .ini file.
 */
void inkINI_close_file(inkINI_file file);

/**
 * Reads an integer value from a file with a given key.
 *
 * Assumes that the value being read exists and is an integer value.
 */
int inkINI_read_i(inkINI_file file, char* key);

#endif
