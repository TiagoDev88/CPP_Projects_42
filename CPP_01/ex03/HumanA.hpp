


#include <iostream>
#include "Weapon.hpp"

class HumanA
{
    private:
    std::string _name;
    Weapon& _type;

    public:
    HumanA(std::string name, Weapon& type);
    ~HumanA();
    void attack();
};