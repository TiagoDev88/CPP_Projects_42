#ifndef CONTACT_H
# define CONTACT_H

#include <string>
#include <iomanip>
#include <iostream>
#include <cctype>

class Contact {

	public:
		Contact();
		~Contact();
		std::string get_firstname(void);
		std::string get_lastname(void);
		std::string get_nickname(void);
		std::string get_phonenumber(void);
		std::string get_darkestsecret(void);
		void set_firstname(std::string firstname);
		void set_lastname(std::string lastname);
		void set_nickname(std::string nickname);
		void set_phonenumber(std::string phonenumber);
		void set_darkest_secret(std::string darkest_secret);
		void new_contact(Contact *contact);

	private:
		std::string _first_name;
		std::string _last_name;
		std::string _nickname;
		std::string _phone_number;
		std::string _darkest_secret;
};

#endif