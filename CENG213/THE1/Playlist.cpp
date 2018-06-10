#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Playlist.hpp"
#include "Entry.hpp"

using namespace std;


Playlist::Playlist()
{
    srand(15);
}

int Playlist::getRandomNumber(int i, int n) const
{
    int range=n-i;
    int random = rand() % range + i;
    return random;
}

void Playlist::print()
{
    cout << "[PLAYLIST SIZE=" << entries.getSize() <<"]";
    entries.print();
}
void Playlist::printHistory()
{
    cout<<"[HISTORY]";
    history.print();
}

/* TO-DO: method implementations below */

void Playlist::load(string fileName) {
	ifstream ss;
	ss.open(fileName.c_str());
	if (!ss.good()){
        cout << endl << "Unable to open the given file" << endl;
        return;
    }
	string line;
	Node<Entry> *qq = entries.getHead();
	while(getline(ss,line)){
		string token1,token2,token3;
		token1 = line.substr(0,line.find(";"));
		token2 = line.substr(line.find(";") + 1,line.rfind(";") - token1.length() - 1);
		token3 = line.substr(line.rfind(";") + 1, line.length());
		Entry *p = new Entry(token1,token2,token3);
		entries.insertNode(entries.getTail(),*p);
		HistoryRecord *pp = new HistoryRecord(INSERT,*p);
		history.push(*pp);
		delete p;
		delete pp;
	}
	ss.close();
	
}

void Playlist::insertEntry(const Entry &e){
	
	Entry *p = new Entry(e.getTitle(), e.getGenre(), e.getYear());
	entries.insertNode(entries.getTail(),*p);
	HistoryRecord *pp = new HistoryRecord(INSERT,*p);
	history.push(*pp);
	delete p;
	delete pp;
}

void Playlist::deleteEntry(const std::string &_title){
	Entry* p = new Entry(_title);
	Node<Entry>* pp = entries.findNode(*p);
	if(pp == NULL) return;	
    Entry* w = new Entry(pp -> getData().getTitle(), pp -> getData().getGenre(), pp -> getData().getYear());
	delete p;
	pp = entries.findPrev(*w);
	entries.deleteNode(pp);
	HistoryRecord *ppw = new HistoryRecord(DELETE,*w);
	history.push(*ppw);
	delete ppw;
	delete w;
}

void Playlist::moveLeft(const std::string &title){
	Entry* p = new Entry(title);
	Node<Entry>* node = entries.findNode(*p);
	if(node != entries.getHead()){
		Node<Entry>* left_node = entries.findPrev(node -> getData());
		if(left_node != entries.getHead()){
		Node<Entry>* most_left_node = entries.findPrev(left_node -> getData());
		Node<Entry>* tmp = left_node;
		most_left_node -> setNext( left_node -> getNext());
		left_node -> setNext(node -> getNext());
		node -> setNext(left_node);
		}
		else{
			entries.setHead(node);
			Node<Entry>* tmp = node -> getNext();
			node -> setNext(left_node);
			left_node -> setNext(tmp);
		}
		Node<Entry>* search = entries.getHead();
		while(search && search -> getNext()){
			search = search -> getNext();
		}
		entries.setTail(search);
	}
	delete p;

}

void Playlist::moveRight(const std::string &title){
	Entry* p = new Entry(title);
	Node<Entry>* node = entries.findNode(*p);
	if(node != entries.getTail()){
		Node<Entry>* left_node = entries.findPrev(node -> getData());
		if(left_node != NULL){
		Node<Entry>* right_node = node -> getNext();
		Node<Entry>* tmp = right_node -> getNext();
		left_node -> setNext(right_node);
		right_node -> setNext(node);
		node -> setNext(tmp);
		}
		else{
			Node<Entry>* tmp = node -> getNext();
			entries.setHead(node -> getNext());
			node -> setNext(tmp -> getNext());
			tmp -> setNext(node);
		}
		Node<Entry>* search = entries.getHead();
		while(search && search -> getNext()){
			search = search -> getNext();
		}
		entries.setTail(search);
	}
	delete p;
}

void Playlist::reverse(){
	Node<Entry> *p = entries.getHead();
	MyStack<Entry> stack;
	while(p = entries.getHead()){
	stack.push(p -> getData());
	entries.deleteNode(NULL);
	}
	while(!stack.isEmpty()){
		entries.insertNode(entries.getTail(), stack.Top() -> getData());
		stack.pop();
	}
	HistoryRecord *ppw = new HistoryRecord(REVERSE);
	history.push(*ppw);
	delete ppw;
}

void Playlist::merge(const Playlist & pl){
    LinkedList<Entry> list;
    Node<Entry> *left = entries.getHead();
    Node<Entry> *right = pl.entries.getHead();
    while(left and right){
        Entry *q_entry;
        if(left -> getData().getTitle() < right -> getData().getTitle()){
            list.insertNode(list.getTail(), left -> getData());
            left = left -> getNext();
        }
        else{
            list.insertNode(list.getTail(), right -> getData());
            right = right -> getNext();
        }
    }
    if(left == NULL && right != NULL){
        while(right){
            list.insertNode(list.getTail(), right -> getData());
            right = right -> getNext();
        }
    }
    else if(left != NULL and right == NULL){
        while(left){
            list.insertNode(list.getTail(), left -> getData());
            left = left -> getNext();
        }
    }
    entries = list;
    list.clear();
}
/*void Playlist::merge(const Playlist & pl){
    Node<Entry> *p = entries.getHead();
    Node<Entry> *q = pl.entries.getHead();
    while(q && p){
        if(q -> getData().getTitle() < p -> getData().getTitle()){
            entries.insertNode(entries.findPrev( p -> getData()), q -> getData());
            q = q -> getNext();
        }
        else{
        	p = p -> getNext();
        }
    }
    if(p == NULL && q != NULL){
    	while(q){
    		entries.insertNode(entries.getTail(), q -> getData());
 			q = q -> getNext();
    	}
    }
}*/

void Playlist::undo() {
    Node<HistoryRecord> *record = history.Top();
    HistoryRecord record1(record -> getData().getOperation(), record -> getData().getEntry());
    history.pop();
    if(record1.getOperation() == DELETE){
        entries.insertNode(entries.getTail(), record1.getEntry());
    }
    else if(record1.getOperation() == REVERSE){
        reverse();
        history.pop();
    }
    else if(record1.getOperation() == INSERT){
        entries.deleteNode(entries.findPrev(record1.getEntry()));
    }
    
}

void Playlist::shuffle() {
	Node<Entry> *head_pointer = entries.getHead();
	Node<Entry> *q = entries.getHead();
	Node<Entry> *p = entries.getHead();
	Node<Entry> *prev1, *prev2;
	int number, len = entries.getSize();
	for(int i = 0; i < len - 1; ++i){
		q = head_pointer;
		p = entries.getHead();
		number = getRandomNumber(i, len);
		for(int k = 0; k < number; ++k){
			p = p -> getNext();
		}
		if(q == p) {
			head_pointer = entries.getHead();
			for(int t = 0; t < i; ++t){
				head_pointer = head_pointer -> getNext();
			}
			head_pointer = head_pointer -> getNext();
			continue;
		}
		for(int z = 0; z < number - i; ++z){
			moveLeft(p -> getData().getTitle());
		}
		for(int z = 0; z < number - i - 1; ++z){
			moveRight(q -> getData().getTitle());
		}
		/*
		string token1 = q -> getData().getTitle();
	    string token2 = q-> getData().getGenre();
	    string token3 = q -> getData().getYear();
		Entry *q1 = new Entry(token1, token2, token3);
		token1 = p -> getData().getTitle();
	    token2 = p-> getData().getGenre();
	    token3 = p -> getData().getYear();
		Entry *p1 = new Entry(token1, token2, token3);
		prev1 = entries.findPrev(q-> getData());
		prev2 = entries.findPrev(p-> getData());
		entries.deleteNode(prev1);
		entries.deleteNode(prev2);
		entries.insertNode(prev2, *q1);
		entries.insertNode(prev1, *p1);
		cout << "qqwq" << q -> getData() << endl;
		cout << "ppwp" << p -> getData() << endl;
		entries.print();
		delete p1;
		delete q1;*/
		head_pointer = entries.getHead();
		for(int t = 0; t < i; ++t){
		head_pointer = head_pointer -> getNext();
		}
		head_pointer = head_pointer -> getNext();
		
	}
}



void Playlist::sort() {
	Node<Entry> *head_pointer = entries.getHead();
	Node<Entry> *q, *min, *find;
	int len = entries.getSize(), j = 0;
	for(int i = 0; i < len - 1; ++i){
		min = head_pointer;
		q = min -> getNext();
		j = 0;
		while(q){
			if(q -> getData().getTitle() < min -> getData().getTitle()){
				min = q;
			}
			q = q -> getNext();
		}
		find = entries.getHead();
		while(find){
			if(find == min) break;
			find = find -> getNext();
			j++;
		}
		for(int k = 0; k < j - i; ++k){
			moveLeft(min -> getData().getTitle());
		}
		head_pointer = entries.getHead();
		for(int t = 0; t < i; ++t){
		head_pointer = head_pointer -> getNext();
		}
		head_pointer = head_pointer -> getNext();
	}
}



/*void Playlist::sort(){
	int i, len = entries.getSize(), min, k, j;
	Node<Entry>* p, *q, *prev1, *prev2, *tmp, *node1_next, *node2_next;
	for(i = 0; i < len - 1; ++i){
		min = i;
		p = entries.getHead();
		for( j = 0; j < i; ++j){ 		//finding minth node
			p = p -> getNext();
		}
		for(j = i + 1; j < len; ++j){
			q = entries.getHead();
			for(k = 0; k < j; ++k){			//find jth node
				q = q -> getNext(); 
			}
			if(q -> getData().getTitle() < p -> getData().getTitle()){
				min = j;
			}
		}
		cout << p -> getData() << endl;
		cout << q -> getData() << endl;

		prev1 = entries.findPrev(p -> getData());
		prev2 = entries.findPrev(q -> getData());

		cout << prev1<< endl;
		cout << prev2 << endl;
		cout << "aaaaaaaaaaaa"<< i << endl;
		if(i == 1) entries.print();
		cout << "after print" << endl;
		if(len == 2){
			entries.setHead(q);
			q -> setNext(p);
			p -> setNext(NULL);
			return ;
		}
		if(prev1 == NULL){
			node1_next = p -> getNext();
			cout << node1_next -> getData() << endl;
			cout << q -> getNext()<< endl;
			node2_next = q -> getNext();
			entries.setHead(q);
			q -> setNext(node1_next);

			prev2 -> setNext(p);
			p -> setNext(node2_next);
		}
		else{
			cout << prev1 -> getData()<< endl;
			cout << prev2 -> getData()<< endl;
			prev1 -> setNext(q);
			tmp = q -> getNext();
			q -> setNext(p -> getNext());
			prev2 -> setNext(p);
			p -> setNext(tmp);
		}
	}



}*/

/*void Playlist::sort(){
	LinkedList<Entry> list;
	Node<Entry> *prev, *p, *qq;
	string min = "zzzzzzzzzzzzz";
	p = entries.getHead();
	if(p == NULL) return ;
	while(entries.getHead()){
	while(p != NULL){
			cout << "xx" << p -> getData() << endl;
		if(p -> getData().getTitle() < min){
			min = p -> getData().getTitle();
		}
		p = p -> getNext();
	}
	qq = entries.find(min);


	}

	cout << "print";
	list.print();
	cout << "print";
	list.clear();
}*/
