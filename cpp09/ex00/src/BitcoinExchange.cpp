#include "../inc/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
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
    std::ifstream f(db.c_str());
    if (!f.is_open())
        throw std::runtime_error("Error: could not open file.");

    std::string line;
    std::getline(f, line);
    while(std::getline(f, line))
    {
        if(line.empty())
            continue;
        
        std::string::size_type pos = line.find(',');
        if (pos == std::string::npos)
            throw std::runtime_error("Error: bad database line: " + line);
        
        std::string date = line.substr(0, pos);
        if (!isValidDate(date))
            throw std::runtime_error("Error: not valid date." + date);
        std::string exchangeRate = line.substr(pos + 1);

        char *end;
        double rate = std::strtod(exchangeRate.c_str(), &end);
        if (exchangeRate.empty() || *end != '\0' || rate < 0)
            throw std::runtime_error("Error: bad exchange_rate in database: " + line);

        _dataBase[date] = static_cast<float>(rate);
    }
}

void BitcoinExchange::readInput(const std::string &input) const
{
    std::ifstream f(input.c_str());
    if (!f.is_open())
        throw std::runtime_error("Error: could not open file.");

    std::string line;
    std::getline(f, line);
    while(std::getline(f, line))
    {
        if(line.empty())
            continue;

        std::string::size_type pos = line.find('|');
        if (pos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        
        std::string date = line.substr(0, pos);
        int trim = 0;
        for(std::string::size_type i = 10; i < date.size(); i++)
        {
            if(date[i] == 32 || date[i] == 9) // trim
                trim++;
        }
        date.resize(pos - trim);
        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string valueRate = line.substr(pos + 1);

        char *end;
        double value = std::strtod(valueRate.c_str(), &end);
        if (valueRate.empty() || *end != '\0')
                {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        else if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        else if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        try
        {
            float rate = getRateFromDb(date);
            std::cout << date << " => " << value << " = " << rate * static_cast<float>(value) << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    
    for(std::string::size_type i = 0; i < date.size(); i++)
    {
        if(i == 4 || i == 7)
            continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (day < 1 || month < 1 || month > 12)
        return false;

    int lastDayOfMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // last day of months

    int lastDay = lastDayOfMonths[month - 1];

    bool leapYear = false;
    // divisible by 4 and not by 100. Or divisible by 400 for years it ends in 00. (1000, 2000, 3000)
    if( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        leapYear = true;
    
    if (month == 2 && leapYear)
        lastDay = 29;
    return day <= lastDay;
}

float BitcoinExchange::getRateFromDb(const std::string &date) const
{
    std::map<std::string, float>::const_iterator it = _dataBase.upper_bound(date);

    if (it == _dataBase.begin())
        throw std::runtime_error("Error: no earlier date in database => " + date);
    --it; // find the date upper, so going to back to retrieve the small or equal
    return it->second;
}
