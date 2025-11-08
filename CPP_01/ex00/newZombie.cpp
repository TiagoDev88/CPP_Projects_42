

#include "Zombie.hpp"

Zombie* newZombie( std::string name )
{
	Zombie *newZombies = new Zombie(name);
	return newZombies;
}