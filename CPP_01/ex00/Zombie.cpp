

#include "Zombie.hpp"

Zombie::Zombie(std::string name){

	std::cout << name << " Constructor called" << std::endl;
	this->_name = name;
}

Zombie::~Zombie()
{
	std::cout << "Passou aqui\n";
	std::cout << this->_name << " Destructor called" << std::endl;
}

std::string Zombie::GetName(void)
{
	return this->_name;
}

void Zombie::SetName(std::string name)
{
	this->_name = name;
}

void Zombie::announce(void)
{
	std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
