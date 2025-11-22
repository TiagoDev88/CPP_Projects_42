
#include "Replace.hpp"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cout << "./SedIsForLosers <filename> string1 string2" << std::endl;
        return -1;
    }
    std::string file = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    // std::cout << argv[1];
    // std::cout << file;
    // std::fstream ficheiro(file.c_str());
    replaceString(file, s1, s2);
    
    return 0;
}