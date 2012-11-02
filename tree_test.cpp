#include "BST.h"
#include <iostream>

int main() {
  BST<int>* bst = new BST<int>();

  bst->insert(5);
  bst->insert(6);
  bst->insert(3);
  bst->insert(2);
  bst->insert(7);

  bst->print();

  std::cout << std::endl;

  bst->remove(3);
  bst->print();

  std::cout << std::endl;
  
  bst->breadthPrint();
  
  delete bst;

  BST<std::string>* str = new BST<std::string>();
  
  str->insert("A");
  str->insert("Z");
  str->insert("J");
  str->insert("E");
  str->insert("D");
  str->insert("C");
  str->insert("B");
  str->insert("Q");
  
  str->breadthPrint();
  
  delete str;
}
