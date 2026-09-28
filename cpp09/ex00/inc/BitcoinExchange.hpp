#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <exception>


class BitcoinExchange
{
    private:
        std::map<std::string, float> _dataBase;
        float getRateFromDb(const std::string &date) const;
        static bool isValidDate(const std::string &date);
        
        public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();
        
        void readDatabase(const std::string &db);
        void readInput(const std::string &input) const;
};
