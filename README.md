# Red BlackTree Implementation
# I wrote the code referenced by [The article](https://www.cnblogs.com/lengyue365/p/5140831.html)

## after deletion 
```cpp
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
```
```cpp
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
```

```cpp
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
```

```cpp
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
```
