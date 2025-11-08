

#include "Zombie.hpp"

int main(void)
{
	Zombie *tiago = newZombie("TIAGO");
	randomChump("Kiko");

	tiago->announce();
	delete tiago;
	return 0;
}