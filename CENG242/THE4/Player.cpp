#include "Player.h"
#include <iostream>
#include <string>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/


Player::Player(uint id, int x, int y) : id(id), coordinate(x,y) {
	
}

std::string Player::getBoardID() const {
	std::string res;
	if(id < 10)
		res = "0" + std::to_string(id);
	else
		res = std::to_string(id);
	return res;
}

void Player::setHP(int x){
	HP = x;
}
uint Player::getID() const {
	//std::cout << this << std::endl;
	return id;
}

int Player::getHP() const {
	return HP;
}

bool Player::isDead() const {
	return (HP <= 0);
}

const Coordinate& Player::getCoord() const {
	return coordinate;
}

Player::~Player() {
	;
}


void Player::executeMove(Move move) {
	
	if(move != NOOP or move != ATTACK){
		Coordinate new_coordinate = coordinate + move;
		coordinate = new_coordinate;
		if(move == UP)
		std::cout << getFullName() << "(" << getHP() << ")" << "moved UP." << std::endl;
		if(move == DOWN)
		std::cout << getFullName() << "(" << getHP() << ")" << "moved DOWN." << std::endl; 
		if(move == LEFT)
		std::cout << getFullName() << "(" << getHP() << ")" << "moved LEFT." << std::endl; 
		if(move == RIGHT)
		std::cout << getFullName() << "(" << getHP() << ")" << "moved RIGHT." << std::endl; 
	}
}

bool Player::attackTo(Player *player) {
	if(this == player)
		return false;
	int damage_done = Entity::damageForWeapon(this -> getWeapon());
	int damage_absorb = Entity::damageReductionForArmor(player -> getArmor());
	int damage_net = damage_done - damage_absorb;
	if(damage_net < 0 )
		damage_net = 0;
	player -> setHP( player -> getHP() - damage_net);
	std::cout << this -> getFullName() << "(" << this -> getHP() << ") attacked " << player -> getFullName() << "(" << player -> getHP() << ")! (-" << damage_net << ")" << std::endl;
	
	return (player -> isDead());
}


/*bool Player::operator<(const Player &rhs) const {
	return (this -> id < rhs.id);
}*/