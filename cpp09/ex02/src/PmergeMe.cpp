#include "../inc/PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) 
: _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        _vec = other._vec;
        _deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

static void jacobsthalNumbers(std::size_t number)
{

}

void PmergeMe::run(int argc, char** argv)
{
    int i = 1;
    while (i < argc)
    {
        std::cout << argv[i][0];

        if (std::isdigit(argv[i][0]))
        {
            _input.push_back(std::stoi(std::string(argv[i])));
        }
        else
            std::cout << "Nao e digito nem espaco\n";
        i++;
    }
    sortVector(_input);
    
    std::cout << std::endl;
    
    for (size_t i = 0; i < _input.size(); i++)
    {
        std::cout << _input[i] << ", " << std::endl;
    }
    
}

// Merge-Insertion Sort ==  Ford-Johnson

std::vector<int> PmergeMe::sortVector(std::vector<int>& vec)
{
    std::vector<int> high;
    std::vector<int> low;

    // vec[0] = 100;
    for(size_t i = 0; i < vec.size(); i++)
    {
        if (vec[i] > vec[i + 1])
        {
        //     std::cout << "vec[i] " << vec[1];
        //     std::cout << " vec[i + 1] " << vec[0 + 1];
        //     high.push_back(vec[i]);
        //     low.push_back(vec[i + 1]);
        }
        // else
        // {
        //     high.push_back(vec[i + 1]);
        //     low.push_back(vec[i]);
        // }
    }
    // sortVector(high);
    _vec = high;
    return _vec;
}

std::deque<int> PmergeMe::sortDeque(std::deque<int>& deq)
{
    
}