#include <iostream>

#include "BST.h"

int main() {
    BST<int> tree;
    BSTNode<int> *successor;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    tree.insert(10);
    tree.insert(5);
    tree.insert(7);
    tree.insert(6);
    tree.insert(15);
    tree.insert(13);
    tree.insert(14);

    successor = tree.getSuccessor(tree.search(10), preorder);
    if (!successor)
        std::cout << "Successor is NULL" << '\n';
    else
        std::cout << successor->data << '\n';

    /*
    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);
    */

    return 0;
}
