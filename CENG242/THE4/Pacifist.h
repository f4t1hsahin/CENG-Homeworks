#ifndef HW4_PACIFIST_H
#define HW4_PACIFIST_H


#include "Player.h"

class Pacifist : public Player {
public:
    Pacifist(uint id, int x, int y);

    // Name     : Pacifist
    // Priority : { UP, LEFT, DOWN, RIGHT }

    // Armor    : METAL
    // Weapon   : NOWEAPON
    // HP       : 100

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES/OVERRIDES BELOW
    virtual Armor getArmor() const;
    virtual Weapon getWeapon() const;
    virtual const std::string getFullName() const;
    virtual Color::Code getColorID() const;
    virtual std::vector<Move> getPriorityList() const;
    
};


#endif //HW4_PACIFIST_H
