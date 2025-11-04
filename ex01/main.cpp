
#include "PhoneBook.hpp"

int main(void){

	Phonebook Phone;

	std::string line;

	std::cout << "---Welcome to Phonebook---" << std::endl;
	while (true)
	{
		std::cout << "\nPlease enter a command: ";
		std::cout << "(ADD, SEARCH, EXIT)" << std::endl;
		if(!std::getline(std::cin, line))
			break;
		if (line == "SEARCH")
			Phone.Search_Contact();
		else if (line == "ADD")
			Phone.Add_Contact();
		else if (line == "EXIT")
			break;
		else
			std::cout << "Invalid option!" << std::endl;
	}
	return 0;
}