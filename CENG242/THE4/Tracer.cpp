#include "Tracer.h"
using namespace std;
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Tracer::Tracer(uint id, int x, int y) : Player(id,x,y) {
	HP = 100;
}


Armor Tracer::getArmor() const {
	return BRICK;
}
Weapon Tracer::getWeapon() const {
	return SHOVEL;
}
const std::string Tracer::getFullName() const {
	return ("Tracer" + ( (id < 10) ? ("0" + to_string(id)) : to_string(id)));
}
Color::Code Tracer::getColorID() const {
	return (Color::Code(33));
}

std::vector<Move> Tracer::getPriorityList() const {
	std::vector<Move> tmp = { UP, LEFT, DOWN, RIGHT, ATTACK };
	return tmp;
}