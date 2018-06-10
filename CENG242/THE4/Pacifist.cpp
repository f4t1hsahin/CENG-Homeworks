#include "Pacifist.h"
using namespace std;

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Pacifist::Pacifist(uint id, int x, int y) : Player(id,x,y) {
	HP = 100;
}


Armor Pacifist::getArmor() const {
	return METAL;
}
Weapon Pacifist::getWeapon() const {
	return NOWEAPON;
}
const std::string Pacifist::getFullName() const {
	return ("Pacifist" + ( (id < 10) ? ("0" + to_string(id)) : to_string(id)));
}
Color::Code Pacifist::getColorID() const {
	return (Color::Code(32));
}

std::vector<Move> Pacifist::getPriorityList() const {
	std::vector<Move> tmp = { UP, LEFT, DOWN, RIGHT };
	return tmp;
}