#include "Ambusher.h"
using namespace std;

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Ambusher::Ambusher(uint id, int x, int y) : Player(id,x,y) {
	HP = 100;
}

Armor Ambusher::getArmor() const {
	return NOARMOR;
}
Weapon Ambusher::getWeapon() const {
	return SEMIAUTO;
}
const std::string Ambusher::getFullName() const {
	return ("Ambusher" + ( (id < 10) ? ("0" + to_string(id)) : to_string(id)));
}
Color::Code Ambusher::getColorID() const {
	return (Color::Code(34));
}

std::vector<Move> Ambusher::getPriorityList() const {
	std::vector<Move> tmp = { ATTACK };
	return tmp;
}