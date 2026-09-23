#pragma once

#include <iostream>
#include <fstream>
#include <map>


class BitcoinExchange
{
    private:
    std::map<std::string, double> _dataBase;
    
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();
};
