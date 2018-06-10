#include "Board.h"
#include <iostream>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Board::Board(uint boardSize, std::vector<Player *> *players) : boardSize(boardSize){
	this -> players = players;
	storm_level = Entity::stormWidthForRound(1);
}

Board::~Board(){
	;
}

uint Board::getSize() const {
	return boardSize;
}

bool Board::isCoordInBoard(const Coordinate& coord) const {
	if(coord.x >= 0 && coord.x < boardSize && coord.y >= 0 && coord.y < boardSize)
		return true;
	return false;
}

Player * Board::operator[](const Coordinate& coord) const {
	for(int i = 0; i < players -> size(); ++i){
		if((*players)[i] -> getCoord() == coord)
			return (*players)[i];
	}
	return NULL;
}

bool Board::isStormInCoord(const Coordinate &coord) const {
	if(coord.x == boardSize/2 && coord.y == boardSize/2)
		return false;
	if(!isCoordInBoard(coord))
		return false;
	if(coord.x >= storm_level && coord.x < boardSize - storm_level && coord.y >= storm_level && coord.y < boardSize - storm_level)
		return false;
	return true;
}


bool Board::isCoordHill(const Coordinate& coord) const {
	if(boardSize % 2 == 1 && coord.x == boardSize / 2 && coord.y == boardSize / 2)
		return true;
	return false;
}


void Board::updateStorm(uint currentRound) {
	/*if(Entity::stormWidthForRound(currentRound) > boardSize/2)
		storm_level = boardSize/2;
	else */
	storm_level = Entity::stormWidthForRound(currentRound);
}


Coordinate Board::calculateCoordWithMove(Move move, const Coordinate &coord) const {
	if(move == ATTACK or move == NOOP)
		return coord;
	Coordinate new_coord = coord + move;
	if(this -> operator[](new_coord) != NULL)
		return coord;
	if(!isCoordInBoard(new_coord))
		return coord;
	return new_coord;
}


std::vector<Coordinate> Board::visibleCoordsFromCoord(const Coordinate &coord) const {
	std::vector<Coordinate> tmp;
	if(!isCoordInBoard(coord))
		return tmp;
	Coordinate up = coord + UP;
	Coordinate down = coord + DOWN;
	Coordinate left = coord + LEFT;
	Coordinate right = coord + RIGHT;
	if(isCoordInBoard(up))
		tmp.push_back(up);
	if(isCoordInBoard(down))
		tmp.push_back(down);
	if(isCoordInBoard(right))
		tmp.push_back(right);
	if(isCoordInBoard(left))
		tmp.push_back(left);
	return tmp;

}