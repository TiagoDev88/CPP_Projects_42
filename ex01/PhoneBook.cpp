
#include "PhoneBook.hpp"

Phonebook::Phonebook()
{
	this->_count_contacts = 0;
}

Phonebook::~Phonebook(){}

void Phonebook::Add_Contact(void){

	int index = _count_contacts % 8;
	if (_count_contacts == 8){
		std::cout << "Warning: Phonebook is full!" << std::endl;
		std::cout << "New contact replace the oldest contact of list" << std::endl;
	}
	_contact[index].new_contact(&_contact[index]);
	this->_count_contacts++;
	std::cout << "Contact added at index " << index << "!" << std::endl;
}

void Phonebook::Search_Contact(void){
	
	std::cout << "     Index|First Name| Last Name|  Nickname" << std::endl;
	std::cout << "----------|----------|----------|----------" << std::endl;
	for (int i = 0; i < this->_count_contacts && i < 8; i++){
		std::cout << std::setw(10) << i << "|";
		std::string first_name = _contact[i].get_firstname();

		if (first_name.length() > 10)
			first_name = first_name.substr(0, 9) + ".";

		std::cout << std::setw(10) << first_name << "|";
		std::string last_name = _contact[i].get_lastname();

		if (last_name.length() > 10)
			last_name = last_name.substr(0, 9) + ".";

		std::cout << std::setw(10) << last_name << "|";
		std::string nickname = _contact[i].get_nickname();

		if (nickname.length() > 10)
			nickname = nickname.substr(0, 9) + ".";
			
		std::cout << std::setw(10) << nickname << "|" << std::endl;
	}
}

