#include "Berserk.h"
using namespace std;

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Berserk::Berserk(uint id, int x, int y) : Player(id,x,y) {
	HP = 100;
}

Armor Berserk::getArmor() const {
	return WOODEN;
}
Weapon Berserk::getWeapon() const {
	return PISTOL;
}
const std::string Berserk::getFullName() const {
	return ("Berserk" + ( (id < 10) ? ("0" + to_string(id)) : to_string(id)));
}
Color::Code Berserk::getColorID() const {
	return (Color::Code(31));
}

std::vector<Move> Berserk::getPriorityList() const {
	std::vector<Move> tmp = { ATTACK, UP, LEFT, DOWN, RIGHT };
	return tmp;
}