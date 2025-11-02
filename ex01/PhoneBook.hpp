#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include <iostream>
#include "Contact.hpp"

class Phonebook{

	public:
		Phonebook();
		~Phonebook();

		void init(void);
		void Add_Contact(void);
		void Search_Contact(std::string line);
		int plus_index(void);

	private:
		Contact _contact[8];
		int _index;
		int _count_contacts;
};

#endif