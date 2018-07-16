#include <iostream>
#include "RedBlackTree.h"


RedBlackTree *rbtree = new RedBlackTree();

int main() {

    rbtree->insert(10);
    rbtree->insert(20);
    rbtree->insert(40);
    rbtree->insert(50);

    rbtree->insert(2);


    rbtree->insert(98);
   // rbtree->insert(50);
   // rbtree->insert(23);


    rbtree->debugTraverse();
    return 0;
}