
#include "Replace.hpp"

void replaceString(std::string& file, std::string& s1, std::string& s2)
{
    std::fstream f(file.c_str());

    if (f.is_open())
    {
        std::string read;
        if (getline(f, read))
        {
            if (int s = read.find(s1))
            {
                std::cout << s << "\n";
                std::string line = read;
                std::cout << line;

            }
        }
            // std::cout << read;
        f.close();
    }
    else
        std::cerr << "Error! Cannot Open file!" << std::endl;
}