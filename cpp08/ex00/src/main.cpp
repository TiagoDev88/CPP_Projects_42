#include "../inc/easyfind.hpp"

#include <vector>
int main()
{
    std::vector<int> nums = {1,3,5,7,9};

    for (std::vector<int>::iterator it = nums.begin(); it != nums.end() ; ++it)
        std::cout << *it << std::endl;

    std::vector<int> tmp = easyfind(nums, 3);
    return 0;
}