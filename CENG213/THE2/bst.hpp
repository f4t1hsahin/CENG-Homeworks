#ifndef _BIN_SEARCH_TREE_H_
#define _BIN_SEARCH_TREE_H_

#include <functional>
#include <cstddef>
#include <stack>
#include <list>
#include <ostream>
#include <iostream>
using namespace std;
//do not add any other library
//modify parts as directed by assignment text & comments here

template <typename Key, typename Object, 
          typename Comparator=std::less<Key> >
class BinarySearchTree 
{
  private: //do not change
    struct BinaryNode //node definition: a dependent type
    {
      Key key; //keys will be kept constant
      Object data; //objects that are referred to by keys may change
      BinaryNode * left;
      BinaryNode * right;
      size_t height; //height info should be updated per insert & delete

      BinaryNode(const Key &, const Object &,
                 BinaryNode *, BinaryNode *, size_t =0);
    };

  public: //do not change except for your own private utility functions
    class Iterator //iterator class will encapsulate the location within the BST
    {
      public:
        Iterator( ); //dummy constructor for type declaration purposes
        Iterator & operator++( ); //inorder increment
 
        Object & operator*( );  //update data
        const Object & operator*( ) const; //view data

        bool operator==(const Iterator & rhs) const; //compare iterators
        bool operator!=(const Iterator & rhs) const; //compare iterators
      
      private:
        BinaryNode * current; //position
        const BinaryNode * root; //for error check not implemented
        std::stack<BinaryNode *> s; //will be used to conduct in order traversal if
        bool useStack; //this variable is set to true, ignored in == and !=
      private:
        Iterator(BinaryNode *, const BinarySearchTree &, bool =true);
        //other private utility functions can be declared by you
        BinaryNode * inorder_successor_recurs(  BinaryNode* , BinaryNode *);
        BinaryNode * inorderx_successor_recurs( BinaryNode* , BinaryNode *);
        BinaryNode * inorderSuccessor( BinaryNode *);
        BinaryNode * rightMostNode(const BinaryNode* & node);
        BinaryNode * rightxMostNode(const BinaryNode*  node);
        BinaryNode * leftMostNode(const BinaryNode* & node);
        BinaryNode * leftMostNode(BinaryNode*  node);
        Comparator lessThan;

      friend class BinarySearchTree<Key, Object, Comparator>; 
    };

  public: //do not change
    BinarySearchTree( ); //empty tree
    ~BinarySearchTree( ); //reclaim all dyn allocated mem

    void insert(const Key &, const Object &); //to insert new key,item
    void remove(const Key &); //remove the node with the key value (and also data) 

  public: //do not change
    Iterator find(const Key &) const; //single item
    std::list<Iterator> find(const Key &, const Key &) const;//range queries

    Iterator begin( ) const; //inorder begin
    Iterator end( ) const; //dummy NULL iterator

  public: //do not change
    int height( ) const; //return height of the tree
    size_t size( ) const; //return the number of items in the tree
    bool empty( ) const; //return whether the tree is empty or not
    void print(std::ostream &) const;
  
  private: //do not change
    BinaryNode * root; //designated root
    size_t nodes; //number of nodes 
    Comparator isLessThan; //function object to compare keys

  private:
    /* private utility functions that are implemented */
    void makeEmpty(BinaryNode * &);

    BinaryNode * find(const Key &, BinaryNode *) const;
    int height(BinaryNode *) const;
    void print(BinaryNode *, std::ostream &) const;

    template <typename T> //static utility function
    static const T & max(const T &, const T &);


    //balancing functions
    void rotateWithLeftChild(BinaryNode * &);
    void rotateWithRightChild(BinaryNode * &);
    void doubleWithLeftChild(BinaryNode * &);
    void doubleWithRightChild(BinaryNode * &);
    
    //you may add your own private utility functions down here
    void insert_helper(BinaryNode* &, BinaryNode* &);
    void delete_helper(const Key &, BinaryNode* &);
    BinaryNode* mostLeftNode(BinaryNode* );
    void makeNull(const Key &, BinaryNode* &);
    void makeBalanced(BinaryNode* &root);

  private: //not copiable, DO NOT IMPLEMENT or change
    BinarySearchTree(const BinarySearchTree &);
    const BinarySearchTree & operator=(const BinarySearchTree &);
};

//node constructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::BinaryNode::
BinaryNode(const K & _k, const O & _d,
           BinaryNode * _l, BinaryNode * _r, size_t _h)
  : key(_k), data(_d), left(_l), right(_r), height(_h)
{
}


//default constructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::BinarySearchTree( )
  : root(NULL), nodes(0) 
{
}

//destructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::~BinarySearchTree( )
{
  makeEmpty(root);
}

//private utility function for destructor, do not change
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::makeEmpty(BinaryNode * & t)
{
  if (t != NULL)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    --nodes;
  }

  t = NULL;
}

template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::mostLeftNode(BinaryNode* root){
  BinaryNode* tmp = root;
  while(tmp != NULL and tmp -> left != NULL){
    tmp = tmp -> left;
  }
  return tmp;
}

template <typename K, typename O, typename C>
void 
BinarySearchTree<K,O,C>::insert_helper(BinaryNode* & x, BinaryNode* & root){
  if(root == NULL){
    root = x;
  }

  else if(isLessThan(x -> key,root -> key)){
    insert_helper(x, root -> left);
    if(height(root -> left) - height(root -> right) == 2){
      if(isLessThan(x -> key, root -> left -> key))
        rotateWithLeftChild(root);
      else
        doubleWithLeftChild(root);
    }
  }
    else if( isLessThan(root -> key, x -> key)){
      insert_helper(x, root -> right);
      if(height(root -> right) -  height(root -> left) == 2){
        if(isLessThan(root -> right -> key, x -> key))
          rotateWithRightChild(root);
        else
          doubleWithRightChild(root);
      }
    }
    else ;
    root -> height = max(height(root -> left), height(root -> right)) + 1;
  }


template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::makeBalanced(BinaryNode* & root){
  if(root == NULL) return;
  makeBalanced(root -> left);
  makeBalanced(root -> right);
  if(height(root -> left) - height(root -> right) == 2){
    if(height(root -> left -> left) - height(root -> left -> right) > 0)
      rotateWithLeftChild(root);
    else {
      doubleWithLeftChild(root);
    }
  }
  else if(height(root -> left) - height(root -> right) == -2){
    if(height(root -> right -> left) - height(root -> right -> right) > 0)
      doubleWithRightChild(root);
    else
      rotateWithRightChild(root);
  }
}


//public function to insert into BST, IMPLEMENT
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::insert(const K & k, const O & x)
{
  BinaryNode* find_node = find(k, root);
  if(find_node != NULL){
    O * x1 = new O(x);
    find_node -> data = *x1;
    delete x1;
    return ;
  }
  
  BinaryNode* new_node = new BinaryNode(k, x, NULL, NULL, 0);
  insert_helper(new_node, root);
  nodes++;


}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::makeNull(const K& k, BinaryNode* & root){
  if(root == NULL){
    return ;
  }
  else if(isLessThan(k, root -> key)){
    makeNull(k, root -> left);
    root -> height = max(height(root -> left), height(root -> right)) + 1;
  }
  else if(isLessThan(root -> key, k)){
    makeNull(k, root -> right);
    root -> height = max(height(root -> left), height(root -> right)) + 1;
  }
  else{
    root = (root -> left) ? root -> left : root -> right;
  }
}



template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::delete_helper(const K & k, BinaryNode* & root){
  if(root == NULL){
    return ;
  }
  else if(isLessThan(k, root -> key)){
    delete_helper(k, root -> left);
    root -> height = max(height(root -> left), height(root -> right)) + 1;
  }
  else if(isLessThan(root -> key, k)){
    delete_helper(k, root -> right);
    root -> height = max(height(root -> left), height(root -> right)) + 1;
  }
  else if(root -> right != NULL and root -> left != NULL){
    BinaryNode* tmp = root;
    root = mostLeftNode(root -> right);
    makeNull(root -> key, tmp);
    root -> left = tmp -> left;
    root -> right = tmp -> right;
    root -> height = max(height(root -> left), height(root -> right)) + 1;
    delete tmp;
  }
  else{
    BinaryNode* tmp = root;
    root = (root -> left) ? root -> left : root -> right;
    delete tmp; 
  }
}


//public function to remove key, IMPLEMENT
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::remove(const K & k)
{
  if(find(k, root) == NULL) return ;
  delete_helper(k,root);
  makeBalanced(root);
  nodes--;
}

//public function to search elements, do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::find(const K & key) const
{
  BinaryNode * node = find(key, root);

  if (node == NULL)
  {
    return end();
  }
  else
  {               //not inorder iterator
    return Iterator(node, *this, false);
  }
}

/*
 * private utility function to search elements
 * do not change
 */
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::find(const K & key, BinaryNode * t) const
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (isLessThan(key, t->key))
  {
    return find(key, t->left);
  }
  else if (isLessThan(t->key, key))
  {
    return find(key, t->right);
  }
  else //found
  {
    return t;
  }
}

//range queries those within range are inserted to the list
//IMPLEMENT
template <typename K, typename O, typename C>
std::list<typename BinarySearchTree<K,O,C>::Iterator>
BinarySearchTree<K,O,C>::find(const K & lower, const K & upper) const
{
  std::list<Iterator> lst;
  Iterator it;
  for(it = begin(); it != end(); ++it)
  {
    if(  ( isLessThan(lower, it.current -> key) or ( !isLessThan(lower, it.current -> key) and !isLessThan(it.current -> key, lower) ) ) and ( (isLessThan(it.current -> key, upper) or ( !isLessThan(it.current -> key, upper) and !isLessThan(upper, it.current -> key) ) ))){
      typename BinarySearchTree<K,O,C>::Iterator *it1 = new Iterator(it.current, *this,false);

      lst.push_back(*it1);
      delete it1;
  }
}
  return lst;
}

//INORDER iterator begins at ++root, do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::begin() const
{
  return Iterator(root, *this);
}

//no more increment after end() also
//returned in case of unsuccessful search
//or when no more applicance of ++ is possible
//do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::end() const
{
  return Iterator(NULL, *this);
}

//public function to return height, do not change
template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::height( ) const
{
  return height(root);
}

/* private utility function for computing height */
//do not change
template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::height(BinaryNode * t) const
{
  return (t == NULL) ? -1 : t->height;
}

//public function to return number of nodes in the tree
//do not change
template <typename K, typename O, typename C>
size_t
BinarySearchTree<K,O,C>::size( ) const
{
  return nodes;
}

//public true if empty false o.w.
//do not change
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::empty( ) const
{
  return nodes == 0;
}

//public function to print keys inorder to some ostream
//do not change
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::print(std::ostream & out) const
{
  print(root, out);
  out << '\n';
}

/* private utility function to print, do not change */
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::print(BinaryNode * t, std::ostream & out) const
{
  if (t != NULL && t->left != NULL) 
  {
    out << '[';
    print( t->left, out );
  }
  else if (t != NULL && t->left == NULL && t->right != NULL)
  {
    out << "[";
  }

  if (t != NULL)
  {
    if (t->left == NULL && t->right == NULL)
    {
      out << '(' << (t->key) << ')';
    }
    else if (t->left != NULL || t->right != NULL)
    {
      out << '{' << (t->key) << ",H" << t->height << '}';
    }
  }
  
  if (t != NULL && t->right != NULL)
  {
    print( t->right, out );
    out << ']';
  }
  else if (t != NULL && t->left != NULL && t->right == NULL)
  {
    out << "]";
  }
}

/* static function to compute maximum of two elements */
//do not change
template <typename K, typename O, typename C>
template <typename T>
const T &
BinarySearchTree<K,O,C>::max(const T & el1, const T & el2)
{
  return el1 > el2 ? el1 : el2;
}

/* ROTATIONS, do not change */
template <typename K, typename O, typename C>
void 
BinarySearchTree<K,O,C>::rotateWithLeftChild(BinaryNode * & k2)
{
  BinaryNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = BinarySearchTree<K,O,C>::max(height(k2->left), 
                                            height(k2->right)) + 1;
  k1->height = BinarySearchTree<K,O,C>::max(height(k1->left), 
                                            height(k2)) + 1;
  k2 = k1;
}

template <typename K, typename O, typename C>
void 
BinarySearchTree<K,O,C>::rotateWithRightChild(BinaryNode * & k1)
{
  BinaryNode *k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->height = BinarySearchTree<K,O,C>::max(height(k1->left), 
                                            height(k1->right)) + 1;
  k2->height = BinarySearchTree<K,O,C>::max(height(k2->right), 
                                            height(k1)) + 1;
  k1 = k2;
}

template <typename K, typename O, typename C>
void 
BinarySearchTree<K,O,C>::doubleWithLeftChild(BinaryNode * & k3)
{
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}

template <typename K, typename O, typename C>
void 
BinarySearchTree<K,O,C>::doubleWithRightChild(BinaryNode * & k1)
{
  rotateWithLeftChild(k1->right);
  rotateWithRightChild(k1);
}

/* ITERATOR functions */

// dummy constructor, do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::Iterator::Iterator( ) 
  : current(NULL), root(NULL), useStack(false)
{
}

// dereferencing operator non-const version, IMPLEMENT
template <typename K, typename O, typename C>
O &
BinarySearchTree<K,O,C>::Iterator::operator*( )
{
  return current -> data;
}

// dereferencing operator const version, IMPLEMENT
template <typename K, typename O, typename C>
const O & 
BinarySearchTree<K,O,C>::Iterator::operator*( ) const
{
  return current -> data;
}

template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::Iterator::leftMostNode(const BinaryNode* & node)
{
    return leftMostNode(node);
}

template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::Iterator::leftMostNode(BinaryNode*  node)
{
    BinaryNode* tmp = node;
    while (tmp != NULL && tmp->left != NULL)
        
        tmp = tmp->left;
    return tmp;
}


 
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::Iterator::rightMostNode(const BinaryNode* & node)
{

    return rightxMostNode(node);
}

template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::Iterator::rightxMostNode(const BinaryNode*  node)
{
    const BinaryNode* tmp = node;
    while (tmp != NULL && tmp->right != NULL)
        tmp = tmp->right;
    return tmp;
}

template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::Iterator::inorderx_successor_recurs(BinaryNode* root, BinaryNode* x){
    if (root == NULL)
        return NULL;
    BinaryNode* temp;
    if (root==x || (temp = inorder_successor_recurs(root->left,x)) ||
                   (temp = inorder_successor_recurs(root->right,x)))
    {
        if (temp)
        {
            if (root->left == temp)
            {
                return root;
            }
        }
        return root;
    }
    return NULL;
}

template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::Iterator::inorder_successor_recurs(BinaryNode* root, BinaryNode* x){
    return inorderx_successor_recurs(root, x);
}



template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::Iterator::inorderSuccessor( BinaryNode* x)
{
    const BinaryNode* tmp = root;
    if(x -> right != NULL){
      return leftMostNode(x -> right);
    }
    BinaryNode* result = NULL;
    while(tmp != NULL){
      if(lessThan(x -> key, tmp -> key)){

        result = const_cast<BinaryNode*>(tmp);
        tmp = tmp -> left;
      }
      else if(lessThan(tmp -> key, x -> key)){

        tmp = tmp -> right;
      }
      else{
        
        break;
      }
    }
    return result;



    /*// Case1: If right child is not NULL
    cout << x -> key << endl;
    if (x->right != NULL)
    {
        BinaryNode* inorderSucc = leftMostNode(x -> right);
          return inorderSucc;
    }
 

    // Case2: If right child is NULL
    if (x->right == NULL)
    {   
        
        BinaryNode* rightMost = rightMostNode(root);

 
        // case3: If x is the right most node
        if (rightMost == x)
            return NULL;

        else{
          return inorder_successor_recurs(const_cast<BinaryNode*>(root), x);
        }
    }
  */
}



// compare Iterators ignoring useStack var, do not change
template <typename K, typename O, typename C>
bool 
BinarySearchTree<K,O,C>::Iterator::
operator==(const Iterator & rhs) const
{ 
  return current == rhs.current && 
         root == rhs.root; 
}

// compare Iterators ignoring useStack var, do not change
template <typename K, typename O, typename C>
bool 
BinarySearchTree<K,O,C>::Iterator::
operator!=(const Iterator & rhs) const
{ 
  return !(*this == rhs); 
}

// increment Iterator to point to the inorder next
// node of then-current node, in case that no further
// advances are possible return an Iterator that is
// equal to end( ) , IMPLEMENT
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator &
BinarySearchTree<K,O,C>::Iterator::operator++( )
{
  if(useStack == false){
    current = NULL;
  }

  current = inorderSuccessor(current);
  return *this;
}

/* real Iterator constructor will be invoked by 
 * BST member function only. if no inorder iterator
 * is required by the computation designer should 
 * explicitly set useStack variable to false, o.w.
 * it will be assumed to be true. IMPLEMENT
 */
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::Iterator::
Iterator(BinaryNode * p, const BinarySearchTree & rhs, bool stk)
{
  current = p;
  root = rhs.root;
  useStack = stk;
  if(useStack){
    current = leftMostNode(p);
  }
}


#endif
