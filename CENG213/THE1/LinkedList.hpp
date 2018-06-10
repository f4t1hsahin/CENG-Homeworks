#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
	      size_t  size;
    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        /* Return head of the linked-list*/
        Node<T>* getHead() const;
        /* Set head of the linked-list*/
        Node<T>* setHead(Node<T>* n);
        /* Return tail of the linked-list*/
        Node<T>* getTail() const;
        /* Set tail of the linked-list*/
        Node<T>* setTail(Node<T>* n);
        /* Get the previous node of the node that contains the data item.
         * If the head node contains the data item, this method returns NULL.*/
        Node<T>* findPrev(const T& data) const;
        /* Get the node that stores the data item.
         * If data is not found in the list, this function returns NULL.*/
        Node<T>* findNode(const T& data) const;
        /* Insert a new node to store the data item.
         * The new node should be placed after the “prev” node.
         * If prev is NULL then insert new node to the head.*/
        void insertNode(Node<T>* prev, const T& data);
        /* This method is used to delete the node that is next to “prevNode”.
         * PS:prevNode is not the node to be deleted. */
        void deleteNode(Node<T>* prevNode);
        /* This method is used to clear the contents of the list.*/
        void clear();
        /* This method returns true if the list empty, otherwise returns false.*/
        bool isEmpty() const;
        /* This method returns the current size of the list. */
        size_t getSize() const;
        /*Prints the list. This method was already implemented. Do not modify.*/
        void print() const;
};

template <class T>
void LinkedList<T>::print() const{
    const Node<T>* node = head;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */

template<class T>
LinkedList<T>::LinkedList(): head(NULL), tail(NULL), size(0) {}


template<class T>
Node<T>* LinkedList<T>::getHead() const{
  return head;
}

template<class T>
Node<T>* LinkedList<T>::getTail() const{
  return tail;
}

template<class T>
Node<T>* LinkedList<T>::setHead(Node<T>* n){
  head = n;
  return head;
}

template<class T>
Node<T>* LinkedList<T>::setTail(Node<T>* n){
  tail = n;
  return tail;
}

template<class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const{
  Node<T> *p = head;
  while(p -> getNext()){
    if(p -> getNext() -> getData() == data){
      return p;
    }
    p = p -> getNext();
  }
  return NULL;
}


template<class T>
Node<T>* LinkedList<T>::findNode(const T& data) const{
  Node<T> *p = head;
  while(p){
    if(p -> getData() == data){
      return p;
    }
    p = p -> getNext();
  }
  return NULL;
}

template<class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data){
  int flag = 1;
  Node<T> *newNode = new Node<T>(data);
  Node<T> *tmp = head;
  if(prev == NULL){ //if head == NULL0;
    if(head == NULL) flag = 0;
    newNode -> setNext(head);
    head = tail = newNode;
    
    if(flag == 0){
      size++;
      return ;
    }
  }
  else{
    newNode -> setNext(prev -> getNext());
    prev -> setNext(newNode);
  }
  while(tmp -> getNext()){
    tmp = tmp -> getNext();
  }
  tail = tmp;
  size++;
}

template<class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode){
  Node<T> *tmp = head;
  if(prevNode != NULL && prevNode -> getNext() == NULL) return ;
  if(prevNode != NULL){
    Node<T> *tmp = prevNode -> getNext();
    prevNode -> setNext(tmp -> getNext());
    delete tmp;
    tmp = head;
  }
  else{
    head = head -> getNext();
    delete tmp;
    tmp  = head;
  }
  while(tmp && tmp -> getNext()){
    tmp =tmp -> getNext();
  }
  tail = tmp;
  size--;
}

template<class T>
bool LinkedList<T>::isEmpty() const{
  return head == NULL;
}

template<class T>
size_t LinkedList<T>::getSize() const{
  return size;
}

template<class T>
void LinkedList<T>::clear(){
  Node<T>*p = getHead();

  while(p && p -> getNext()){
    deleteNode(p);
  }
  delete getHead();
  size = 0;
  head = NULL;
  tail = NULL;
}

template<class T>
LinkedList<T>::~LinkedList(){
  clear();
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll){
  if(this != &ll){
    clear();
    const Node<T>* r = ll.getHead();
    Node<T>* q = head;
    if(r == NULL) *this;
    insertNode(q,r -> getData());
    r = r -> getNext();
    q = head;
    while(r){
      insertNode(q, r -> getData());
      r = r -> getNext();
      q = q -> getNext();
    }
  }
  return *this;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll){
  head = tail = new Node<T>();
  *this = ll;
}



/* end of your implementations*/

#endif
