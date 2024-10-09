#include "inkINI/inkINI.hpp"

#include <iostream>

namespace inkINI
{

ini_file::ini_file(const std::string& filename)
    : m_file {filename}
{
    std::cout << m_file.is_open() << '\n';
}

}
