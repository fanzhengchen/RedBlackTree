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

/**
 * insertion balance
 * @param rt
 */
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
    if (delNode == nullptr || delNode == nullNode) {
        return;
    }
    Node *replaceNode = nullptr;
    if (delNode->ch[0] != nullNode) {
        findPre(delNode, value, replaceNode);
    } else if (delNode->ch[1] != nullNode) {
        findSuc(delNode, value, replaceNode);
    } else {
        replaceNode = delNode;
    }

    std::swap(delNode->value, replaceNode->value);

    puts("delete\n");
    replaceNode->debug();

    doDeletion(replaceNode);
}

/**
 * delete balance
 * @param rt
 */
void RedBlackTree::balance(Node *rt) {
    if (rt == root) {
        return;
    }


    Node *par = rt->parent;
    bool c = par->isRightChild();
    Node *brother = par->ch[c ^ 1];



    /**
     *
     *    B                 (B)
     *   / \                / \
     * (B)  B     ----->   B   R
     *     / \                / \
     *    B   B              B   B
     */
    if (par->color == BLACK && brother->color == BLACK && brother->ch[0] == BLACK
        && brother->ch[1] == BLACK) {
        brother->color = RED;
        balance(par);
        return;
    }



    /**
     *        B1            B3
     *       / \   ---->   /
     *    (B)2  R3        R1
     *                    /
     *                  (B)2
     *
     *   grantee that brother is not red in the following
     */
    if (brother->color == RED) {
        std::swap(brother->color, par->color);
        rotate(brother);
    }



    /**
     *     R                 (B)
     *    / \                / \
     *  (B)  B    ----->    B   R
     *      / \                / \
     *     B   B              B   B
     */
    assert(brother->color == BLACK);
    brother = par->ch[c ^ 1];
    if (par->color == RED && brother->color == BLACK && brother->ch[0] == BLACK
        && brother->ch[1] == BLACK) {
        std::swap(par->color, brother->color);
        balance(par);
        return;
    }

    /**
     *      X              X
     *     / \            / \
     *   (B)  B2   -->  (B)  B1
     *       / \              \
     *      R1  B3             R2
     *                          \
     *                           B3
     */

    Node *left = brother->ch[0];
    if (left->color == RED) {
        std::swap(brother->color, left->color);
        rotate(left);
    }


    /**
     *       X1                     X2
     *      / \                    /  \
     *    (B)  B2     ----->      B1   B4
     *        / \                / \
     *       X3  R4            (B)  X3
     */
    Node *right = brother->ch[1];
    if (right->color == RED) {
        std::swap(brother->color, par->color);
        right->color = BLACK;
        rotate(brother);
    }

}

/**
 * denote the root of the subtree contains the deleted node is N
 * @param rt
 */
void RedBlackTree::doDeletion(Node *rt) {
    /**
     * at least one child is null
     */
    //assert(rt->ch[0] != nullNode && rt->ch[1] != nullNode);

    /**
     * case 1
     * deleted node is root
     */
    if (rt == root) {
        root = nullNode;
        delete (rt);
        return;
    }


    /**
     * real delete the node rt;
     */
    Node *par = rt->parent;
    bool c = rt->isRightChild();
    bool k = (rt->ch[1] != nullNode);
    Node *next = rt->ch[k];
    par->ch[c] = next;
    if (next != nullNode) {
        next->parent = par;
    }
    delete (rt);
    /**
     * case 2
     * one child is red
     */
    if (next != nullNode && next->color == RED) {
        next->color = BLACK;
        return;
    }

    /**
     * it's balanced ..... both child are null and itself must be black and father is red
     */
    if (next == nullNode && par->color == RED) {
        par->color = BLACK;
        return;
    }

    /**
     * now we must balance the rb tree recursively
     */
    balance(par);

}


void RedBlackTree::traverse(Node *rt) {
    if (rt != nullNode) {
        traverse(rt->ch[0]);
        rt->debug();
        traverse(rt->ch[1]);
    }

}

void RedBlackTree::debugTraverse() {

    printf("debug root %s %d\n\n", root->color ? "R" : "B", root->value);
    traverse(root);
}