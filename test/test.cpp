#include <iostream>
#include "inkINI/inkINI.hpp"

int main()
{
    std::cout << std::boolalpha;

    inkINI::ini_file file {"a.ini"};

    return 0;
}
