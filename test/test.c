#include "inkINI/inkINI.h"

int main(int argc, char** argv)
{
    inkINI_file ini_file = inkINI_load_file("test/ini-files/a.ini");

    inkINI_close_file(ini_file);

    return 0;
}
