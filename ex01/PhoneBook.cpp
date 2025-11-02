
#include "PhoneBook.hpp"

Phonebook::Phonebook()
{
	// std::cout << "Constructor Called Phonebook\n";
}

Phonebook::~Phonebook(){
	// std::cout << "Destructor Called Phonebook\n";
}

void Phonebook::init(void){
	this->_index = 0;
	this->_count_contacts = 0;
}

int Phonebook::plus_index(){
	this->_index += 1;
	return this->_index;
}

void Phonebook::Add_Contact(void){

	if (_count_contacts == 8){
		std::cout << "Warning: Phonebook is full!" << std::endl;
		std::cout << "New contact replace the first contact of list" << std::endl;
	}
	_contact[_index].new_contact(&_contact[_index]);

}

// void Phonebook::Search_Contact(std::string line){

	
// }