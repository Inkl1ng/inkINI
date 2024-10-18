#include "inkINI/inkINI.h"

int main(int argc, char** argv)
{
    inkINI_file file = inkINI_load_file(INI_FILES "a.ini");
    inkINI_print_all(file);

    putchar('\n');

    printf("key: %s\tvalue: %s\n", "name", inkINI_read_s(file, "name"));
    printf("key: %s\tvalue: %i\n", "age", inkINI_read_i(file, "age"));
    printf("key: %s\tvalue: %i\n", "income", inkINI_read_i(file, "income"));
    printf("key: %s\tvalue: %i\n", "num_cars", inkINI_read_i(file, "num_cars"));
    printf("key: %s\tvalue: %f\n", "debt", inkINI_read_d(file, "debt"));

    inkINI_write_s(file, "name", "John McNutt");
    inkINI_write_i(file, "age", 18);

    putchar('\n');

    inkINI_print_all(file);

    inkINI_close_file(file, INI_FILES "b.ini");

    return 0;
}
