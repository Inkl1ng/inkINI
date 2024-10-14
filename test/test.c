#include "inkINI/inkINI.h"

void print_all_values(inkINI_file file, int num_entries)
{
    printf("num_values: %i\n", num_entries);
    for (size_t i = 0; i < num_entries; ++i) {
        printf("index: %zu\tkey: %s\tvalue: %s\n",
               i,
               file.entries[i].key,
               file.entries[i].value);
    }
}

int main(int argc, char** argv)
{
    inkINI_file ini_file = inkINI_load_file(INI_FILES "a.ini");
    print_all_values(ini_file, 5);

    putchar('\n');

    printf("key: %s\tvalue: %s\n", "name", inkINI_read_s(ini_file, "name"));
    printf("key: %s\tvalue: %i\n", "age", inkINI_read_i(ini_file, "age"));
    printf("key: %s\tvalue: %i\n", "income", inkINI_read_i(ini_file, "income"));
    printf("key: %s\tvalue: %i\n", "num_cars", inkINI_read_i(ini_file, "num_cars"));
    printf("key: %s\tvalue: %f\n", "debt", inkINI_read_d(ini_file, "debt"));

    inkINI_close_file(ini_file);

    return 0;
}
