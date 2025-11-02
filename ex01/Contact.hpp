#ifndef CONTACT_H
# define CONTACT_H

#include <string>
#include <iostream>

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
		void new_contact(Contact *contact);

	private:
		std::string _first_name;
		std::string _last_name;
		std::string _nickname;
		std::string _phone_number;
		std::string _darkest_secret;
};

#endif