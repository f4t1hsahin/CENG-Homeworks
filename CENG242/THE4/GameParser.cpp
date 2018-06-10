#include "GameParser.h"
#include <fstream>
#include <iostream>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

std::pair<int, std::vector<Player *> *> GameParser::parseFileWithName(const std::string& filename) {
	std::vector<Player *> *players = new std::vector<Player *>;
	int board_size, player_count;
	std::fstream fl;
	std::string tmp(""),parse("");
	fl.open(filename.c_str());
	std::getline(fl,tmp);
	parse = tmp.substr(tmp.find(":") + 1, tmp.length());
	board_size = std::stoi(parse);
	std::getline(fl,tmp);
	parse = tmp.substr(tmp.find(":")+1, tmp.length());
	player_count = std::stoi(parse);
	//std::cout << board_size << "         " << player_count << std::endl;
	for(int i = 0; i < player_count; ++i){
		//std::cout << i << std::endl;
		std::getline(fl, tmp);
		std::string id(""),name(""),x(""),y("");
		id = tmp.substr(0, tmp.find(":"));
		tmp = tmp.substr(tmp.find(":") + 2);
		name = tmp.substr(0, tmp.find(":"));
		tmp = tmp.substr(tmp.find(":") + 2);
		x = tmp.substr(0, tmp.find(":"));
		tmp = tmp.substr(tmp.find(":") + 2);
		y = tmp.substr(0, tmp.find(":"));
		int _id, _x, _y;
		_id = std::stoi(id);
		_x = std::stoi(x);
		_y = std::stoi(y);
		//std::cout << "id  " << _id << name << " x  " << _x << "y  " << y << std::endl;
		Player * player_p;
		if(name == "Berserk")
			player_p = new Berserk(_id,_x,_y);
		if(name == "Ambusher")
			player_p = new Ambusher(_id,_x,_y);
		if(name == "Tracer")
			player_p = new Tracer(_id,_x,_y);
		if(name == "Pacifist")
			player_p = new Pacifist(_id,_x,_y);
		if(name == "Dummy")
			player_p = new Dummy(_id,_x,_y);
		players -> push_back(player_p);
	}
	/*for(auto p : *players){
		if(p)
			std::cout << p -> getFullName() << std::endl;
		else
			std::cout << "kekkkekeoekeo" << std::endl;
	}*/
	return (std::make_pair(board_size, players));

}