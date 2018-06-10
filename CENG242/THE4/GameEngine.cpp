#include "GameEngine.h"
#include <climits>
#include <cmath>
#include <iostream>
#include <algorithm>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

void shrink_vector(std::vector<Player *> *players){
	for(int i = 0; i < players -> size(); ++i){
		if((*players)[i] == NULL){
			players -> erase(players -> begin() + i);
		}
	}
}


GameEngine::GameEngine(uint boardSize, std::vector<Player *> *players) : currentRound(1), players(players), boardSize(boardSize), board(boardSize, players) {
	//for(auto player : *players)
		//std::cout << player << std::endl;	
	std::sort(players -> begin(), players -> end() , [](Player* a, Player* b){ return a -> getID() < b -> getID();});

}

GameEngine::~GameEngine(){
	shrink_vector(players);
	for(auto player : *players){
		if(player)
			delete player;
	}
	delete players;
}


const Board& GameEngine::getBoard() const {
	return board;
}


Player* GameEngine::operator[](uint id) const {
	shrink_vector(players);
	for(auto player : *players){
		//std::cout << player << std::endl;
		if( player && player -> getID() == id){
			return player;
		}
	}
	return NULL;
}

bool GameEngine::isFinished() const {
	int size = board.getSize();
	shrink_vector(players);
	//std::cout << "ASLKDJALSKJDALSKDJLASKJD" <<  players -> size() << std::endl;
	//for(auto player : *players)
	//	std::cout << player << std::endl;
	if(players -> size() == 0)
		return true;
	if(players -> size() == 1 && board.isCoordHill((*players)[0] -> getCoord())){
		return true;
	}
	return false;
}

Player * GameEngine::getWinnerPlayer() const {
	if(!isFinished() || players -> size() == 0)
		return NULL;
	if(isFinished()){
		return (*players)[0];
	}
}

Player* get_most_priority(std::vector<Player*> vctr){
	uint min = UINT_MAX;
	Player* res;
	for(auto player: vctr)	{
		if(player && player -> getID() < min){
			min = player -> getID();
			res = player;
		}
	}
	return res;
}




Move GameEngine::takeTurnForPlayer(uint playerID){
	shrink_vector(players);
	Player* player = this -> operator[](playerID);
	if(player == NULL)
		return NOOP;
	//std::cout << player -> getFullName() << std::endl;
	std::vector<Move> pr_lst = player -> getPriorityList();
	std::vector<Coordinate> visible_coords = board.visibleCoordsFromCoord(player -> getCoord());
	if(board.isStormInCoord(player -> getCoord())){
		std::cout << player -> getFullName() << "(" << player -> getHP() << ") is STORMED! (-" <<Entity::stormDamageForRound(currentRound)<< ")" << std::endl;
		player -> setHP(player -> getHP() - Entity::stormDamageForRound(currentRound));
		
	}
	if(player -> isDead()){
		for(int i = 0; i < players -> size(); ++i){
			if((*players)[i] == player){
				(*players)[i] = NULL;
			}
		}
		std::cout << player -> getFullName() << "(" << player -> getHP() << ") is DIED." << std::endl;
		delete player;
		shrink_vector(players);
		Board board(boardSize, players);
		board.updateStorm(currentRound);
		return NOOP;
	}
	if(pr_lst.size() == 0){
		return NOOP;
	}
	for(auto move : pr_lst){
		if(move == NOOP)
			return NOOP;
		if(move == ATTACK){
			std::vector<Player*> attack_players;
			for(auto coor : visible_coords){
				Player* tmp = board[coor];
				if(tmp != NULL)
					attack_players.push_back(tmp);
			}
			if(attack_players.size() == 0)
				continue;
			Player* attack_player = get_most_priority(attack_players);
			bool isPlayerDead = player -> attackTo(attack_player);
			if(isPlayerDead){
				for(int i = 0; i < players -> size(); ++i){
					if((*players)[i] == attack_player){
						(*players)[i] = NULL;
					}
				}
				std::cout << attack_player -> getFullName() << "(" << attack_player -> getHP() << ") is DIED." << std::endl;
				delete attack_player;
				shrink_vector(players);
				Board board(boardSize, players);
				board.updateStorm(currentRound);
				
			}
			return ATTACK;
		}
		else{
			Coordinate new_coord = board.calculateCoordWithMove(move, player -> getCoord());
			Coordinate hill(boardSize/2, boardSize/2);
			if(new_coord != player -> getCoord() && hill - new_coord < hill - player -> getCoord()){
				player -> executeMove(move);
				return move;
			}
			else{
				continue;
			}
		}
	}
}




 void GameEngine::takeTurn(){
 	std::cout << "-- START ROUND " << currentRound << " --" <<std::endl;
 	board.updateStorm(currentRound);
 	shrink_vector(players);
 	uint max_id = (*players)[players -> size() - 1] -> getID();
 	//std::cout << "max_id  " << max_id << std::endl;  
 	//bool arr[max_id] = {false};
 	//std::vector<bool> visited(, 0);
 	for(int i = 0; i < max_id+1; ++i){
 		Player* player = this -> operator[](i);
 		if(player != NULL){
 			//arr[i] = true;
 			takeTurnForPlayer(player -> getID());
 		}
 	}
 	/*for(auto player : *players){
 		if(player != NULL){
 			takeTurnForPlayer(player -> getID());
 		}

 	}*/
 	std::cout << "-- END ROUND " << currentRound << " --" <<std::endl;
 	++currentRound;
 	shrink_vector(players);
 }


 std::vector<Player * > * GameEngine::getPlayers() const {
 	return players;
 }


