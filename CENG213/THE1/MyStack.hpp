#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "Node.hpp"
#include <iostream>
using namespace std;

/*You are free to add private/public members inside this template..*/
template <class T>
class MyStack{
    private:
    Node<T> *top;
    public:
    /*Default constructor*/
    MyStack();
    /*copy constructor*/
    MyStack(const MyStack<T>& rhs);
    /*destructor*/
    ~MyStack();
    /*overloaded = operator*/
    MyStack<T>& operator=(const MyStack<T>& rhs);
    /*returns true if stack is empty*/
    bool isEmpty() const;
    /*push newItem to stack*/
    void push(const T& newItem);
    /*pop item from stack*/
    void pop();
    /*return top item of the stack*/
    Node<T>* Top() const;
	/*Prints the stack entries. This method was already implemented. Do not modify.*/
    void print() const;
};

template <class T>
void MyStack<T>::print() const{
    const Node<T>* node = top;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

/* TO-DO: method implementations below */
template<class T>
MyStack<T>::MyStack() : top(NULL) {}

template<class T>
bool MyStack<T>::isEmpty() const{
  return top == NULL;
}

template<class T>
void MyStack<T>::push(const T& newItem){
  Node<T>* newNode = new Node<T>(newItem);
  newNode -> setNext(top);
  top = newNode;
}

template<class T>
void MyStack<T>::pop(){
  if(!isEmpty()){
    Node<T>* ptr = top;
    top = top -> getNext();
    delete ptr;
  }
}

template<class T>
Node<T>* MyStack<T>::Top() const{
  return top;
}

template<class T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& rhs){ // test et
  if(this != &rhs){

    while(!isEmpty()){
      pop();
    }
    if(!rhs.top) top = NULL;
    else{
      top = new Node<T>(rhs.top -> getData());
      Node<T>* q = rhs.top -> getNext();
      Node<T>* p = top;
      while(q){
        Node<T> *tmp = new Node<T>(q -> getData());
        p -> setNext(tmp);
        p = p -> getNext();
        q = q -> getNext();
      }
      p -> setNext(NULL);
    }
    return *this;
  }
}

template<class T>
MyStack<T>::MyStack(const MyStack<T>& rhs){
  top = NULL;
  *this = rhs;
}

template<class T>
MyStack<T>::~MyStack(){
  while(!isEmpty()) pop();


}

#endif /* MYSTACK_HPP */
