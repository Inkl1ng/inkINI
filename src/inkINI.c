#include "inkINI/inkINI.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*** INCLUDED FROM inkINI.h ***/

inkINI_file inkINI_load_file(char* filename)
{
    // check if file exists
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // create a new file
        // Trying to open a file in "a" mode will create a new
        // file if the specified file doesn't already exist.
        file = fopen(filename, "a");
        fclose(file);
    } else {
        fclose(file);
    }
    // Close the file after the checks and then open in "r+" mode for
    // reading and writing.
    file = fopen(filename, "r+");
    inkINI_file ini_file;
    ini_file.file = file;
    ini_file.entries = malloc(sizeof(struct value) * INKINI_MAX_VALUES);

    // read al the values in the file
    char line[INKINI_MAX_LINE_LENGTH + 1];
    int num_values = 0;
    while (fgets(line, INKINI_MAX_LINE_LENGTH + 1, ini_file.file) != NULL) {
        // ignore empty lines and comments
        if (line[0] == INKINI_COMMENT || strlen(line) == 1) {
            continue;
        }

        int equal_sign_index = 0;
        while (line[equal_sign_index] != '=') {
            // printf("%c", line[equal_sign_index]);
            ++equal_sign_index;
        }

        // get the key for an entry
        int i = 0;
        int j = 0;
        while (i < equal_sign_index) {
            if (line[i] != ' ') {
                ini_file.entries[num_values].key[j] = line[i];
                ++j;
            }
            ++i;
        }
        ini_file.entries[num_values].key[j + 1] = '\0';

        // get the value for an entry
        i = equal_sign_index + 1;
        j = 0;
        bool in_quotes = false;
        while (line[i] != '\n') {
            if (line[i] == '\"') {
                in_quotes = !in_quotes;
            }

            if (line[i] != ' ' || in_quotes) {
                ini_file.entries[num_values].value[j] = line[i];
                ++j;
            }
            ++i;
        }

        ini_file.entries[num_values].value[j + 1] = '\0';

        ++num_values;
    }

    printf("num_values: %i\n", num_values);
    for (int i = 0; i < num_values; ++i) {
        printf("index: %i\tkey: %s\tvalue: %s\n",
               i,
               ini_file.entries[i].key,
               ini_file.entries[i].value);
    }

    return ini_file;
}

void inkINI_close_file(inkINI_file file)
{
    fclose(file.file);
    free(file.entries);
    file.entries = NULL;
}
