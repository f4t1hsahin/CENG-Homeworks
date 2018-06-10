#ifndef HW4_BERSERK_H
#define HW4_BERSERK_H


#include "Player.h"

class Berserk : public Player {
public:
    Berserk(uint id, int x, int y);

    // Name     : Berserk
    // Priority : { ATTACK, UP, LEFT, DOWN, RIGHT }

    // Armor    : WOODEN
    // Weapon   : PISTOL
    // HP       : 100

    // DO NOT MODIFY THE UPPER PART
    // ADD OWN PUBLIC METHODS/PROPERTIES/OVERRIDES BELOW

    virtual Armor getArmor() const;
    virtual Weapon getWeapon() const;
    virtual const std::string getFullName() const;
    virtual Color::Code getColorID() const;
    virtual std::vector<Move> getPriorityList() const;

};


#endif //HW4_BERSERK_H
