#include "../inc/BitcoinExchange.hpp"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: Please put one file an argument\n";
        return -1;
    }
    try
    {
        BitcoinExchange btc;
        btc.readDatabase("data.csv");
        btc.readInput(argv[1]);
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}