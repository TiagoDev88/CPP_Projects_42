#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    readDatabase("../data.csv");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _dataBase(other._dataBase) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _dataBase = other._dataBase;
    return *this;
}
    
BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::readDatabase(const std::string &db)
{
    std::ifstream f(db);
    if (f.is_open())
        throw std::logic_error("Error: could not open file.");

    std::string test;
    while(std::getline(f, test))
    {
        std::cout << test << std::endl;
        std::cout << "entrou\n";
    }
}

void BitcoinExchange::readInput()
{

}