#include "Miner.h"
#include <iomanip>
#include <iostream>
#include "Utilizer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Miner::Miner(std::string name) : name(name) {}

Miner::~Miner(){
	for(int i = 0; i < chains.size(); ++i){
		if(forks[i] != 1){
			delete chains[i];
			chains[i] = NULL;
		}
		else{
			chains[i] -> setHead(NULL);
			delete chains[i];
		}
	}
}

int Miner::getNextAvailableBlockchainID() const {
	int id = 0;
	for(int i = 0; i < chains.size(); ++i){
		if(id == (chains[i]) -> getID()){
			id++;
		}
		else{
			return id;
		}
	}
	return id;
}

void Miner::createNewBlockchain() {
	chains.push_back(new Blockchain(getNextAvailableBlockchainID()));
	forks.push_back(0);
}


void Miner::mineUntil(int cycleCount) {
	for(int i = 0; i < cycleCount; ++i){
		for(int j = 0; j < chains.size(); ++j){
				++(*chains[j]);
		}
	}
}

void Miner::demineUntil(int cycleCount) {
		for(int i = 0; i < cycleCount; ++i){
			for(int j = 0; j < chains.size(); ++j){
				if(forks[j] == 0)	
					--(*chains[j]);
		}
	}
}

long Miner::getBlockchainCount() const {
	return chains.size();
}

Blockchain* Miner::operator[](int id) const {
	for(int i = 0; i < chains.size(); ++i){
		if(chains[i] -> getID() == id)
			return chains[i];
	}
	return NULL;
}


std::ostream& operator<<(std::ostream& os, const Miner& miner) {
	os << "-- BEGIN MINER --" << std::endl;
	os << "Miner name: " << miner.name << std::endl;
	os << "Blockchain count: " << miner.getBlockchainCount() << std::endl;
	os << "Total value: " << std::fixed << std::setprecision(Utilizer::koinPrintPrecision()) << miner.getTotalValue() << std::endl;
	os << std::endl;
	for(int i = 0; i < miner.chains.size(); ++i){
		os << (*(miner.chains[i])) << std::endl;
	}
	os << std::endl;
	os << "-- END MINER --" << std::endl;
	return os;
}


double Miner::getTotalValue() const {
	double total = 0;
	for(int i = 0; i < chains.size(); ++i){
		if(forks[i] != 1)
			total += (chains[i]) -> getTotalValue();
	}
	return total;
}

bool Miner::softFork(int blockchainID) {
	Blockchain* p = NULL;
	for(int i = 0; i < chains.size(); ++i){
		if(chains[i] -> getID() == blockchainID){
			p = chains[i];
			forks[i] = 2;
			break;
		}
	}
	Blockchain *newBlock;
	if(p == NULL){
		return false;
	}
	Koin *q = p -> getHead();
	if(q == NULL){
		newBlock = new Blockchain(getNextAvailableBlockchainID());
		chains.push_back(newBlock);
		forks.push_back(1);
		return true;
	}
	while(q -> getNext()){
		q = q -> getNext();
	}
	newBlock = new Blockchain(getNextAvailableBlockchainID(),q);
	chains.push_back(newBlock);
	forks.push_back(1);
	return true;
}

bool Miner::hardFork(int blockchainID){
	Blockchain* p = this -> operator[](blockchainID);
	Blockchain *newBlock;
	if(p == NULL){
		return false;
	}
	Koin *q = p -> getHead();
	while(q && q -> getNext()){
		q = q -> getNext();
	}
	if(q){
		Koin* newKoin = new Koin(q -> getValue());
		newBlock = new Blockchain(getNextAvailableBlockchainID(),newKoin);
	}
	else{
		newBlock = new Blockchain(getNextAvailableBlockchainID());
	}
	chains.push_back(newBlock);
	forks.push_back(0);
	return true;
}
