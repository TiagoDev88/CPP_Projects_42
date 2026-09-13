#include "../inc/Array.hpp"
#include <iostream>

int main(void)
{
    std::cout << "--- default constructor ---" << std::endl;
    Array<int> empty;
    std::cout << "empty.size() = " << empty.size() << std::endl;

    std::cout << "\n--- unsigned int constructor ---" << std::endl;
    Array<int> nums(5);
    std::cout << "nums.size() = " << nums.size() << std::endl;
    for (unsigned int i = 0; i < nums.size(); i++)
        nums[i] = i * 10;
    for (unsigned int i = 0; i < nums.size(); i++)
        std::cout << "nums[" << i << "] = " << nums[i] << std::endl;

    std::cout << "\n--- copy constructor ---" << std::endl;
    Array<int> copy(nums);
    copy[0] = 999;
    std::cout << "nums[0] = " << nums[0] << " | copy[0] = " << copy[0] << std::endl;

    std::cout << "\n--- copy assignment operator ---" << std::endl;
    Array<int> assigned;
    assigned = nums;
    assigned[1] = -1;
    std::cout << "nums[1] = " << nums[1] << " | assigned[1] = " << assigned[1] << std::endl;

    std::cout << "\n--- operator[] out of bounds ---" << std::endl;
    try
    {
        nums[nums.size()] = 42;
    }
    catch (const std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
    try
    {
        nums[10000] = 42;
    }
    catch (const std::exception& e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }

    std::cout << "\n--- const operator[] ---" << std::endl;
    const Array<int> constNums(nums);
    std::cout << "constNums[0] = " << constNums[0] << std::endl;

    return 0;
}
