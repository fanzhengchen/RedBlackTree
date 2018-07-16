#include <iostream>
#include "RedBlackTree.h"


RedBlackTree *rbtree = new RedBlackTree();

int main() {

    rbtree->insert(10);
    rbtree->insert(120);
    rbtree->insert(98);
    rbtree->insert(128);
    rbtree->insert(12);


    rbtree->debugTraverse();

    rbtree->del(10);
    rbtree->del(12);


    rbtree->debugTraverse();
    return 0;
}