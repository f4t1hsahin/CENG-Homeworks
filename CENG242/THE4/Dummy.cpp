#include "Dummy.h"
using namespace std;

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Dummy::Dummy(uint id, int x, int y) : Player(id,x,y) {
	this -> HP = 1000;
}

Armor Dummy::getArmor() const {
	return NOARMOR;
}
Weapon Dummy::getWeapon() const {
	return NOWEAPON;
}
const std::string Dummy::getFullName() const {
	return ("Dummy" + ( (id < 10) ? ("0" + to_string(id)) : to_string(id)));
}
Color::Code Dummy::getColorID() const {
	return (Color::Code(39));
}

std::vector<Move> Dummy::getPriorityList() const {
	std::vector<Move> tmp = { NOOP};
	return tmp;
}