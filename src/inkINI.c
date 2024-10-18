#include "inkINI/inkINI.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static void read_comment(inkINI_file* file, char* line)
{
    size_t i = 0;
    struct entry* entry = &file->entries[file->num_entries];
    strcpy(entry->value, line);
    entry->key[0] = '\0';
    // remove ending '\n'
    entry->value[strlen(entry->value) - 1] = '\0';
}

static void read_entry(inkINI_file* file, char* line)
{
    struct entry* entry = &file->entries[file->num_entries];
    size_t equal_sign_index = 0;
    while (line[equal_sign_index] != '=') {
        ++equal_sign_index;
    }

    // get the key for an entry
    size_t i = 0;
    size_t j = 0;
    while (i < equal_sign_index) {
        if (line[i] != ' ') {
            entry->key[j] = line[i];
            ++j;
        }
        ++i;
    }
    entry->key[j] = '\0';

    // get the value for an entry
    i = equal_sign_index + 1;
    j = 0;
    bool in_quotes = false;
    while (line[i] != '\n') {
        if (line[i] == '\"') {
            in_quotes = !in_quotes;
        }

        if (line[i] != ' ' || in_quotes) {
            entry->value[j] = line[i];
            ++j;
        }
        ++i;
    }

    entry->value[j] = '\0';
}

// assumes that the value exists
static void get_value(inkINI_file file, const char* key, char** value)
{
    size_t i = 0;
    while (strcmp(file.entries[i].key, key) != 0) {
        ++i;
    }
    *value = file.entries[i].value;
}

static struct entry* get_entry(inkINI_file file, const char* key)
{
    struct entry* entry = NULL;
    // check if value exists
    for (size_t i = 0; i < INKINI_MAX_ENTRIES; ++i) {
        if (strcmp(file.entries[i].key, key) == 0) {
            entry = &file.entries[i];
        }
    }

    // entry not found, create new entry
    if (entry == NULL) {
        entry = &file.entries[file.num_entries];
        ++file.num_entries;
        strcpy(entry->key, key);
    }

    return entry;
}

/*** INCLUDED FROM inkINI.h ***/

inkINI_file inkINI_load_file(const char* filename)
{
    // check if file exists
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // create a new file
        // Trying to open a file in "a" mode will create a new
        // file if the specified file doesn't already exist.
        file = fopen(filename, "a");
    }
    freopen(filename, "r", file);
    inkINI_file ini_file;
    ini_file.entries = malloc(sizeof(struct entry) * INKINI_MAX_ENTRIES);
    ini_file.num_entries = 0;

    // read al the values in the file
    char line[INKINI_MAX_LINE_LENGTH + 1];
    while (fgets(line, INKINI_MAX_LINE_LENGTH + 1, file) != NULL) {
        if (line[0] == INKINI_COMMENT) {
            read_comment(&ini_file, line);
            ++ini_file.num_entries;
        } else if (strlen(line) == 1) {
            continue;
        } else {
            read_entry(&ini_file, line);
            ++ini_file.num_entries;
        }

    }

    fclose(file);

    return ini_file;
}

void inkINI_close_file(inkINI_file file, const char* filename)
{
    // write new data to file
    FILE* f = fopen(filename, "w");
    for (size_t i = 0; i < file.num_entries; ++i) {
        struct entry* entry = &file.entries[i];

        if (entry->key[0] == '\0') {
            fprintf(f, "%s\n", entry->value);
        } else {
            fprintf(f, "%s = %s\n", entry->key, entry->value);
        }
    }

    fclose(f);
    free(file.entries);
    file.entries = NULL;
}

int inkINI_read_i(inkINI_file file, const char* key)
{
    char* value;
    get_value(file, key, &value);
    return atoi(value);
}

double inkINI_read_d(inkINI_file file, const char* key)
{
    char* value;
    get_value(file, key, &value);
    return atof(value);
}

const char* inkINI_read_s(inkINI_file file, const char* key)
{
    char* value;
    get_value(file, key, &value);
    return value;
}

void inkINI_write_i(inkINI_file file, const char* key, int value)
{
    struct entry* entry = get_entry(file, key);
    sprintf(entry->value, "%i", value);
}

void inkINI_write_d(inkINI_file file, const char* key, double value)
{
    struct entry* entry = get_entry(file, key);
    sprintf(entry->value, "%f", value);
}

void inkINI_write_s(inkINI_file file, const char* key, const char* value)
{
    struct entry* entry = get_entry(file, key);
    strcpy(entry->value, value);
}

void inkINI_print_all(inkINI_file file)
{
    printf("num_values: %i\n", file.num_entries);
    for (size_t i = 0; i < file.num_entries; ++i) {
        printf("index: %zu\tkey: %s\tvalue: %s\n",
               i,
               file.entries[i].key,
               file.entries[i].value);
    }
}
