//
// Created by fanzhengchen on 7/16/18.
//

#include "RedBlackTree.h"
#include <cstdio>

class RedBlackTree;

RedBlackTree::RedBlackTree() {
    nullNode = new Node(0, BLACK);
    root = nullNode;
    nullNode->parent = nullNode;
    nullNode->ch[0] = nullNode;
    nullNode->ch[1] = nullNode;
}

RedBlackTree::Node *RedBlackTree::createNode(int value, bool color) {
    RedBlackTree::Node *node = new RedBlackTree::Node(value, color);
    node->ch[0] = node->ch[1] = node->parent = nullNode;
    return node;
}


void RedBlackTree::rotate(Node *rt) {

    Node *father = rt->parent;
    Node *grand = father->parent;


    bool c = (father->ch[1] == rt);
    bool fc = (grand->ch[1] == father);

    Node *&ch = rt->ch[c ^ 1];
    father->ch[c] = ch;
    if (ch != nullNode) {
        ch->parent = father;
    }
    ch = father;
    ch->parent = rt;


    rt->parent = grand;
    grand->ch[fc] = rt;

    if (father == root) {
        root = rt;
    }

}

void RedBlackTree::pushUp(Node *rt) {

    if (rt == root) {
        rt->color = BLACK;
        return;
    }
    Node *par = rt->parent;

    if (rt->color == RED && par->color == RED) {
        Node *grand = par->parent;
        bool fc = (grand->ch[1] == par);
        Node *uncle = grand->ch[fc ^ 1];
        if (uncle->color == RED) {
            uncle->color = par->color = BLACK;
            grand->color = RED;
        } else {
            bool c = (par->ch[1] == rt);
            if (c == fc) {
                par->color = BLACK;
                grand->color = RED;
                rotate(par);
            } else {
                rotate(rt);
                pushUp(rt->ch[c ^ 1]);
            }
        }
    }
}

void RedBlackTree::insert(int value) {
    if (root == nullNode) {
        root = createNode(value, BLACK);
    } else {
        doInsert(root, nullNode, value);
    }
}

void RedBlackTree::doInsert(Node *&rt, Node *par, int value) {
    if (rt == nullNode) {
        rt = createNode(value, RED);
        rt->parent = par;
    } else if (rt->value == value) {
        rt->cnt++;
        return;
    } else {
        bool c = (rt->value < value);
        doInsert(rt->ch[c], rt, value);
    }
    pushUp(rt);
}

void RedBlackTree::findPre(Node *rt, int value, Node *&ret) {
    if (rt == nullNode) {
        return;
    }
    if (rt->value < value) {
        ret = rt;
        findPre(rt->ch[1], value, ret);
    } else {
        findPre(rt->ch[0], value, ret);
    }
}

void RedBlackTree::findSuc(Node *rt, int value, Node *&ret) {
    if (rt == nullNode) {
        return;
    }

    if (rt->value > value) {
        ret = rt;
        findSuc(rt->ch[0], value, ret);
    } else {
        findSuc(rt->ch[1], value, ret);
    }

}


void RedBlackTree::traverse(Node *rt) {
    if (rt != nullNode) {
        traverse(rt->ch[0]);
        rt->debug();
        traverse(rt->ch[1]);
    }

}

void RedBlackTree::debugTraverse() {

    printf("root %s %d\n\n", root->color ? "R" : "B", root->value);
    traverse(root);
}