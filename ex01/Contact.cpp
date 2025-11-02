
#include "Contact.hpp"

Contact::Contact() {

	// std::cout << "Constructor Called Contact\n" ;
	
};

Contact::~Contact() {
	
	// std::cout << "Destructor Called Contact\n";

};

std::string Contact::get_firstname(void){
	return this->_first_name;
}

std::string Contact::get_lastname(void){
	return this->_last_name;
}

std::string Contact::get_nickname(void){
	return this->_nickname;
}

std::string Contact::get_phonenumber(void){
	return this->_phone_number;
}

std::string Contact::get_darkestsecret(void){
	return this->_darkest_secret;
}

void Contact::set_firstname(std::string firstname){
	this->_first_name = firstname;
}

void Contact::new_contact(Contact *contact){
	
}