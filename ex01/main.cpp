
#include "PhoneBook.hpp"

int main(void){

	Phonebook Phone;

	std::string line;

	std::cout << "Welcome to Phonebook" << std::endl;
	Phone.init();
	while (1)
	{
		std::cout << "What do you want to do?" << std::endl;
		std::cout << "SEARCH" << std::endl;
		std::cout << "ADD" << std::endl;
		std::cout << "EXIT" << std::endl;
		std::cin >> line;

		std::cout << line << std::endl;

		if (line == "SEARCH")
			break;
		// Phone.Search_Contact(line);
		else if (line == "ADD")
			Phone.Add_Contact();
		else if (line == "EXIT")
			return 0;
		else
			std::cout << "Invalid option!" << std::endl;
	}
	return 0;
}