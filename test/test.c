#include "inkINI/inkINI.h"

int main(int argc, char** argv)
{
    inkINI_file ini_file = inkINI_load_file("test/ini-files/a.ini");

    putchar('\n');
    printf("key: %s\tvalue: %i\n", "age", inkINI_read_i(ini_file, "age"));
    printf("key: %s\tvalue: %i\n", "income", inkINI_read_i(ini_file, "income"));
    printf("key: %s\tvalue: %i\n", "num_cars", inkINI_read_i(ini_file, "num_cars"));
    printf("key: %s\tvalue: %i\n", "debt", inkINI_read_i(ini_file, "debt"));

    inkINI_close_file(ini_file);

    return 0;
}
