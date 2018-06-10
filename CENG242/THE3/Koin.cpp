#include "Koin.h"
#include "Utilizer.h"
#include <cmath>
#include <iomanip>

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/


Koin::Koin(double value){
	this -> value = value;
	next = NULL;
}

Koin::Koin(const Koin& rhs){
	value = rhs.value;
	next = rhs.next;
}






Koin& Koin::operator=(const Koin& rhs){
	value = rhs.value;
	next = rhs.next;
}
    


Koin::~Koin(){
	;
}

double Koin::getValue() const {
	return value;
}


Koin* Koin::getNext() const{
	return next;
}


void Koin::setNext(Koin *next){
	this -> next = next;
}

 bool Koin::operator==(const Koin& rhs) const {
 	const Koin* p = this, *q = &rhs;
 	bool equal = true;
 	while(p && q){
 		if(std::abs(p->value - q->value) >= Utilizer::doubleSensitivity()){
 			equal = false;
 			break;
 		}
 		p = p -> next;
 		q = q -> next;
 	}
 	if(p || q){
 		equal = false;
 	}
 	return equal;
 }

 bool Koin::operator!=(const Koin& rhs) const {
 	return (!(*this == rhs));
 }

 Koin& Koin::operator*=(int multiplier) {
 	value = value * multiplier;
 	return *this;
 }

 Koin& Koin::operator/=(int divisor) {
 	value = value / divisor;
 	return *this;
 }


std::ostream& operator<<(std::ostream& os, const Koin& koin) {
 	const Koin *p = &koin;
 	while(p){
 		os << std::fixed << std::setprecision(Utilizer::koinPrintPrecision()) <<p -> value << "--";
 		p = p -> next;
 	}
 	os << "|";
 	return os;
 }
