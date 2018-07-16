//
// Created by fanzhengchen on 7/16/18.
//

#include "RedBlackTree.h"
#include <cstdio>
#include <algorithm>

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


RedBlackTree::Node *RedBlackTree::doFind(Node *rt, int value) {
    if (rt == nullNode) {
        return nullNode;
    }
    if (rt->value == value) {
        return rt;
    }

    bool c = rt->value < value;
    return doFind(rt->ch[c], value);

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

void RedBlackTree::del(int value) {
    Node *delNode = doFind(root, value);
    Node *replaceNode = nullptr;
    if (delNode->ch[0] != nullNode) {
        findPre(delNode, value, replaceNode);
    } else if (delNode->ch[1] != nullNode) {
        findSuc(delNode, value, replaceNode);
    } else {
        replaceNode = delNode;
    }

    std::swap(delNode->value, replaceNode->value);
    replaceNode->debug();
    Node *N = replaceNode;
    //doDeletion(N);

    if (N->color == RED) {
        doDeletion(N);
        return;
    }

    /**
     * at least one child is RED
     */
    if (N->ch[0]->color | N->ch[1]->color) {
        doDeletion(N);
        return;
    }


}

/**
 * denote the root of the subtree contains the deleted node is N
 * @param rt
 */
void RedBlackTree::doDeletion(Node *rt) {
    /**
     * the node must have at least one null node
     */
    assert(rt->ch[0] == nullNode || rt->ch[1] == nullNode);

    Node *par = rt->parent;
    bool c = rt->isRight();
    bool isRightChild = (rt->ch[1] != nullNode);
    Node *next = rt->ch[isRightChild];
    next->parent = par;
    if (par != nullNode) {
        par->ch[c] = next;
    }
    if (rt == root) {
        root = next;
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