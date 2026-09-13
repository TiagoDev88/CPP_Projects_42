#include "../inc/iter.hpp"
#include <iostream>

template<typename T>
static void printArray(T const c)
{
    std::cout << "printArray: " << c << std::endl;
}

template<typename T>
static void tenMore(T& c)
{
    c += 10;
}

template<typename T, typename F>
static void createTest(T* c, F& func, std::string fromType)
{

    std::cout << fromType << " type with: ";

    for (size_t i = 0; i < 3; i++)
        std::cout << c[i] << ", ";
    
    std::cout << std::endl;

    ::iter(c, 3, func);
    size_t hasConst = fromType.find("const");
    if (std::string::npos == hasConst)
    {
        std::cout << std::endl;
        std::cout << "After iter with type " << fromType << ": ";

        for (size_t i = 0; i < 3; i++)
            std::cout << c[i] << ", ";
    }
    
    std::cout << std::endl;
    std::cout << std::endl;
}

int main()
{
    int c[3] = {1,2,3};
    char array[4] = "ABC";
    const int cConst[3] = {30, 31, 32};
    const char arrayConst[4] = "DEF";    

    createTest<int>(c, tenMore<int>, "int");
    createTest<char>(array, tenMore<char>, "char");
    createTest<int const>(cConst, printArray<int>, "const int");
    createTest<const char>(arrayConst, printArray<char>, "const char");

    return 0;
}