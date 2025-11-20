


#include <iostream>
#include "Weapon.hpp"

class HumanB
{
    private:
    std::string _name;
    Weapon& _type;

    public:
    HumanB(std::string name, Weapon& type);
    ~HumanB();
    void attack();
};