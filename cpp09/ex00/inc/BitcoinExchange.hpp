#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <exception>


class BitcoinExchange
{
    private:
        std::map<std::string, double> _dataBase;
        void readDatabase(const std::string &db);
        void readInput();
    
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();
};
