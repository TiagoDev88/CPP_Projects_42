#pragma once

#include <cstdlib>
#include <algorithm>
#include <iostream>

template<typename T>
T easyfind(T& container, int sec)
{
    typename T::iterator it = container.begin();
    for (typename T::iterator it = container.begin(); it != container.end(); ++it)
    {
        if (*it == sec)
            std::cout << "ENCONTREI\n";
    }
}