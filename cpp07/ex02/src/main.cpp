#include "../inc/Array.hpp"

int main(void)
{
    Array<int> s;
    Array<int> ola(10);
    std::cout << ola.getArr() << std::endl;

    Array<int> oi = ola;
    std::cout << oi.getArr() << std::endl;
    return 0;
}
