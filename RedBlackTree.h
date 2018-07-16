//
// Created by fanzhengchen on 7/16/18.
//

#ifndef RBTREE_REDBLACKTREE_H
#define RBTREE_REDBLACKTREE_H

#include <cstdio>

#define RED 1
#define BLACK 0

class RedBlackTree {

    struct Node {
        bool color;
        int value;
        Node *ch[2];
        Node *parent;
        int size;
        int cnt;

        Node(int _value, bool _color) : value(_value), color(_color), size(0), cnt(0) {}

        void debug() {
            printf("node %s %d\n", color ? "RED" : "BLACK", value);
            if (parent != nullptr) {
                printf("father %s %d side:%d\n", parent->color ? "RED" : "BLACK", parent->value,
                       this == parent->ch[1]);
            }
            puts("------");
        }

        bool isRight() {
            if (parent != nullptr) {
                return (parent->ch[1] == this);
            }
            return false;
        }
    };

private:
    Node *nullNode;
    Node *root;


    /**
    * child rotate to its father
    * @param c
    */
    void rotate(Node *rt);


    /**
     * count the size of the node
     * @param rt
     */
    void pushUp(Node *rt);

    /**
     * swap the state and value with two nodes
     * @param x
     * @param y
     */
    void swap(Node *x, Node *y);


    /**
     *
     * @param rt
     * @param value
     */
    void doInsert(Node *&rt, Node *par, int value);

    /**
     *
     * @param rt
     */
    void traverse(Node *rt);


    /**
     * try to rebalance when delete node
     * @param rt
     */
    void rebalance(Node *&rt);


    /**
     * real delete
     * @param rt
     */
    void doDeletion(Node *rt);

    Node *doFind(Node *rt, int value);


    Node *createNode(int value, bool color);

public:

    RedBlackTree();

    /**
     * insert with value;
     * @param value
     */
    void insert(int value);

    /**
     * delete value;
     * @param value
     */
    void del(int value);

    /**
     *
     * @param value
     * @return
     */
    Node *find(int value);

    /**
     * find predecessor
     * @param value
     * @return
     */
    void findPre(Node *rt, int value, Node *&ret);

    /**
     * find Successor
     * @param value
     * @return
     */
    void findSuc(Node *rt, int value, Node *&ret);

    /**
     * traverse elemetns;
     */
    void debugTraverse();
};


#endif //RBTREE_REDBLACKTREE_H
