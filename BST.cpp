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
    if(iop->getLeftChild()!=0){                   // node has the in-order predecessor in its children
      iop = iop->getLeftChild();                  // PREPARE FOR TRAVERSAL
      while(iop->getRightChild() != 0){           // traverse to the IOP
        iop = iop->getRightChild();
      }
      iop->setRightChild(*(*curr)->getRightChild());     // set the IOP's right child to be the removeNode's right tree
      Node<T>* temp = *curr;                            // create a temporary pointer so we don't lose the node in mem
      *curr = (*curr)->getLeftChild();                   // redirect the removeNode pointer to its left child
      delete temp;                                      // delete the removeNode
    }
    else if ((*curr)->getRightChild()!=0){            // removeNode does not have a left subtree, so no IOP there
      Node<T>* temp = *curr;                            // pointer so we don't lose the node
      *curr = (*curr)->getRightChild();   // redirect pointer
      delete temp;                                      // delete the removeNode
    }
    else {                                            // Has no children
      Node<T>* temp = *curr;
      *curr = 0;
      delete temp;
    }
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

template class BST<int>;
template class BST<double>;
template class BST<std::string>;
