# Red BlackTree Implementation
# I wrote the code referenced by [The article](https://www.cnblogs.com/lengyue365/p/5140831.html)


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
```
