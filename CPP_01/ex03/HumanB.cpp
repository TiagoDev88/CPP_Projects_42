


#include "HumanB.hpp"

HumanB::HumanB(std::string name, Weapon& type)
{

}

HumanB::~HumanB(){}

void HumanB::attack()
{
    std::cout << _name << " attacks with their " << Weapon::getType() << std::endl;
}