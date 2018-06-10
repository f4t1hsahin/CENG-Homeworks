#ifndef HW4_AMBUSHER_H
#define HW4_AMBUSHER_H


#include "Player.h"

class Ambusher : public Player {
public:
    Ambusher(uint id, int x, int y);

    // Name     : Ambusher
    // Priority : { ATTACK }

    // Armor    : NOARMOR
    // Weapon   : SEMIAUTO
    // HP       : 100

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES/OVERRIDES BELOW
    virtual Armor getArmor() const;
    virtual Weapon getWeapon() const;
    virtual const std::string getFullName() const;
    virtual Color::Code getColorID() const;
    virtual std::vector<Move> getPriorityList() const;
};


#endif //HW4_AMBUSHER_H
