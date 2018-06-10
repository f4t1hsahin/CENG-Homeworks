#include "Blockchain.h"
#include <iostream>
#include "Utilizer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Blockchain::Blockchain(int id) : id(id), head(NULL){}

Blockchain::Blockchain(int id, Koin *head) : id(id), head(head){}

Blockchain::Blockchain(const Blockchain& rhs): id(rhs.id){
	Koin *p, *q = rhs.head;
	if(!q)
		return ;
	head = new Koin(q -> getValue());
	p = head;
	q = q -> getNext();
	while(q){
		p -> setNext((new Koin(q -> getValue())));
		p = p -> getNext();
		q = q -> getNext();
	}

}


Blockchain& Blockchain::operator=(Blockchain&& rhs) noexcept {
	Koin *p = head, *tmp;
	while(p){	
		tmp = p;
		p = p -> getNext();
		delete tmp;
	}
	 head = rhs.head;
	 rhs.head = NULL;
	return *this;
}

Blockchain::~Blockchain(){
	if(head == NULL)
		return ;
	Koin *p;
	while(head){
		p = head;
		head = head -> getNext();
		delete p;
	}
}


int Blockchain::getID() const {
	return id;
}


Koin* Blockchain::getHead() const {
	return head;
}


double Blockchain::getTotalValue() const {
	double tot = 0;
	Koin* p = head;
	while(p){
		tot += p -> getValue();
		p = p -> getNext();
	}
	return tot;
}

long Blockchain::getChainLength() const {
	long len = 0;
	Koin* p = this -> head;
	while(p){
		len += 1;
		p = p -> getNext();
	}
	return len;
}

void Blockchain::operator++(){
	Koin *newKoin = new Koin(Utilizer::fetchRandomValue());
	Koin *p = head;
	if(p == NULL){
		head = newKoin;
		return;
	}
	while(p -> getNext()){
		p = p -> getNext();
	}
	p -> setNext(newKoin);

}

void Blockchain::operator--(){
	Koin *p = head;
	if(p == NULL)
		return ;
	if(p -> getNext() == NULL){
		delete p;
		head = NULL;
		return ;
	}
	while(p -> getNext() && p -> getNext() -> getNext()){
		p = p -> getNext();
	}
	delete (p -> getNext());
	p -> setNext(NULL);
}

Blockchain& Blockchain::operator*=(int multiplier){
	Koin *p = head;
	while(p){
		*p *= multiplier;
		p = p -> getNext();
	}
	return *this;
}


Blockchain& Blockchain::operator/=(int divisor){
	Koin *p = head;
	while(p){
		*p /= divisor;
		p = p -> getNext();
	}
	return *this;
}


std::ostream& operator<<(std::ostream& os, const Blockchain& blockchain) {
	if(blockchain.head == NULL){
		os << "Block " << blockchain.id << ": Empty.";
	}
	else{
		os << "Block " << blockchain.id << ": " << (*blockchain.head) <<"(" <<  blockchain.getTotalValue() << ")";
	}
	return os;
}

void Blockchain::setHead(Koin* head){
	this -> head = head;
}