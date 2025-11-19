
#include "Zombie.hpp"

int main(void)
{
    Zombie* horde = zombieHorde(5, "Kiko");

    for (int i = 0; i < 5; i++)
        horde[i].announce();

    delete[] horde;
}