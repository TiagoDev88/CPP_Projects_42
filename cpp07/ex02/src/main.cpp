#include "../inc/Array.hpp"

int main(void)
{
    Array<int> s;
    Array<int> ola(10);
    // std::cout << ola.getArrSize() << std::endl;

    s = ola;
    Array<int> ze(s);
    // std::cout << oi.getArrSize() << std::endl;
    return 0;
}
