#include "BST.h"
#include <iostream>

template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  
}


template <typename T>
bool BST<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void BST<T>::insert(T v) {
  Node<T>* temp = new Node<T>(v);
  Node<T>** curr = &root;

  while (*curr != 0) {
    if (v < (*curr)->getValue()) {
      curr = &((*curr)->getLeftChild());
    } else if (v > (*curr)->getValue()) {
      curr = &((*curr)->getRightChild());
    }
  }
  *curr = temp;
}

template <typename T>
void BST<T>::remove(T v) {  // in order predecessor swap
  //find node
  Node<T>** curr = &root;
    
  while(*curr != 0 && v!=(*curr)->getValue()) { // finds the node, otherwise the tree is empty/the value was not found
    if(v < (*curr)->getValue())
      curr = &((*curr)->getLeftChild());
    else if(v > (*curr)->getValue())
      curr = &((*curr)->getRightChild());
  }

  Node<T>* iop = *curr; // will become pointer to IOP
  //find IOP
  if(iop != 0){                                   // tree is not empty or the value is in the tree
    Node<T>* temp = *curr;
    if(iop->getLeftChild()!=0){                   // node has the in-order predecessor in its children
      iop = iop->getLeftChild();                  // PREPARE FOR TRAVERSAL
      while(iop->getRightChild() != 0){           // traverse to the IOP
        iop = iop->getRightChild();
      }
      iop->setRightChild(*(*curr)->getRightChild());     // set the IOP's right child to be the removeNode's right tree
      temp = *curr;                            // create a temporary pointer so we don't lose the node in mem
      *curr = (*curr)->getLeftChild();                   // redirect the removeNode pointer to its left child
    }
    else if ((*curr)->getRightChild()!=0){            // removeNode does not have a left subtree, so no IOP there
      temp = *curr;                            // pointer so we don't lose the node
      *curr = (*curr)->getRightChild();   // redirect pointer
    }
    else {                                            // Has no children
      temp = *curr;
      *curr = 0;
    }
    delete temp;
  //If the value wasn't in the tree, or the tree is empty... nothing needs to be done!
  }
}

template <typename T>
void BST<T>::print() {
  traversalPrint(root);
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
  }
}

template <typename T>
void BST<T>::breadthPrint() {
  std::list< Node<T>* >* topLevel = new std::list< Node<T>* >();
  topLevel->push_back(root);
  levelTraversal(topLevel,0);
}

template <typename T>
int BST<T>::depth(Node<T>* root, int dpth, int maxDepth) {

  if(root != 0 && (root->getLeftChild() !=0 || root->getRightChild() !=0)) {
    int leftDepth = depth(root->getLeftChild(),dpth+1,maxDepth);
    int rightDepth = depth(root->getRightChild(),dpth+1,maxDepth);
    if(leftDepth > rightDepth) return leftDepth;
    else return rightDepth;
  }
  else {
    return dpth;
  }
}

template <typename T>
int BST<T>::pow(int a, int p) {
  if(p == 0) return 1;
  else return a*pow(a,p-1);
}

template <typename T>
void BST<T>::levelTraversal(std::list< Node<T>* >* parents, int level) {
  bool keepGoing = false;
  int treeDepth = depth(root,0,0);
  int width = pow(2,treeDepth)*3;
  std::list< Node<T>* >* holder = new std::list< Node<T>* >();
  
  int startSpace = width - 1;
  for(int i = 0; i<level+1; i++) {
    startSpace = startSpace/2;
  }
  int numEls = pow(2,level);
  if(treeDepth != level) {
    for(int i = 0; i<startSpace; i++) {std::cout << " ";} //spacing before the level
  }
  for (int i = 0; i<numEls; i++ ) {
    Node<T>* temp = parents->front();
    parents->pop_front();

    if(temp == 0) {
      holder->push_back((Node<T>*)0);
      holder->push_back((Node<T>*)0);
      std::cout << "-";
    }
    else if(temp->getLeftChild() == 0 && temp->getRightChild() == 0) {
      //do nothing
      holder->push_back((Node<T>*)0);
      holder->push_back((Node<T>*)0);
      std::cout << temp->getValue();
    }
    else if(temp->getLeftChild() == 0) {
      holder->push_back((Node<T>*)0);
      holder->push_back(temp->getRightChild());
      std::cout << temp->getValue();
      keepGoing = true;
    }
    else if(temp->getRightChild() == 0) {
      holder->push_back(temp->getLeftChild());
      holder->push_back((Node<T>*)0);
      std::cout << temp->getValue();
      keepGoing = true;
    }
    else {
      holder->push_back(temp->getLeftChild());
      holder->push_back(temp->getRightChild());
      std::cout << temp->getValue();
      keepGoing = true;
    }
    if(!parents->empty()) {
      int spacing = (width/numEls)-1;
      if(spacing!=2) { // spacing case
        for(int i = 0; i<spacing; i++) {std::cout << " ";}
      }
      else { // case for the bottom row
        if(i%2==0) std::cout << "   ";
        else std::cout << " ";
      }
    }
  }
  if(keepGoing) {
    delete parents;
    int lines = (width/4)-1;
    for(int i = 0; i<level; i++) { lines = lines/2; }
    int inBetweenSpacing = 1;
    int spacing = (width/numEls)-1;
    for(int i = 0; i<lines; i++) {
      std::cout << std::endl;
      spacing = spacing-2;
      startSpace = startSpace - 1;
      for(int j = 0; j<startSpace; j++) {
        std::cout << " ";
      }
      for(int j = 0; j<numEls; j++) {
        std::cout << "/";
        for(int k = 0; k<inBetweenSpacing; k++) {
          std::cout << " ";
        }
        std::cout << "\\";
        for(int l = 0; l<spacing; l++) {
          std::cout << " ";
        }
      }
      inBetweenSpacing = inBetweenSpacing+2;
    }
    std::cout << std::endl;
    levelTraversal(holder, level+1);
  }
  else {
    std::cout << std:: endl;
  }
}

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
