
#include "Contact.hpp"

Contact::Contact() {}

Contact::~Contact() {}

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


void Contact::set_lastname(std::string lastname){
	this->_last_name = lastname;
}

void Contact::set_nickname(std::string nickname){
	this->_nickname = nickname;
}

void Contact::set_darkest_secret(std::string darkest_secret){
	this->_darkest_secret = darkest_secret;
}

void Contact::set_phonenumber(std::string phone){
	this->_phone_number = phone;
}

int is_alpha(std::string s)
{
	int i = 0;
	while (s[i])
	{
		if (!std::isalpha(s[i]) && !std::isspace(s[i]))
			return (0);
		i++;
	}
	return 1;
}

int is_phone_number(std::string s)
{
	int i = 0;
	while (s[i])
	{
		if (std::isdigit(s[i]) || std::isspace(s[i]) || s[i] == '+')
			i++;
		else
			return (0);
	}
	return 1;
}


void Contact::new_contact(Contact *contact){

	std::string line;
	std::cout << "insert firstname\n";
	std::cin >> line;
	while (!is_alpha(line))
	{
		std::cerr << "insert valid name! Only letters\n";
		std::cin >> line;
	}
	contact->set_firstname(line);
	std::cout << "Insert Last name\n";
	std::cin >> line;
	while (!is_alpha(line)){
		std::cerr << "insert valid name! Only letters\n";
		std::cin >> line;
	}
	contact->set_lastname(line);
	std::cout << "Insert Nickname\n";
	std::cin >> line;
	contact->set_nickname(line);
	std::cout << "Insert Phone Number\n";
	std::cin >> line;
	while (!is_phone_number(line))
	{
		std::cerr << "Insert valid phone number! Ex: +351 910 152 420 or 910 152 420";
		std::cin >> line;
	}
	contact->set_phonenumber(line);
	std::cout << "Insert Darkest Secret\n";
	std::cin >> line;
	contact->set_darkest_secret(line);
}
