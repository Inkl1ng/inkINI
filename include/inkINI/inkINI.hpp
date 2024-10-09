#ifndef INK_INKINI_HPP
#define INK_INKINI_HPP

#include <fstream>
#include <string>

namespace inkINI
{

class ini_file
{
public:
    ini_file(const std::string& filename);

private:
    std::fstream m_file;
};



}

#endif
