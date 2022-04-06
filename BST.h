#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    void copy_helper(BSTNode<T> *&r, BSTNode<T> *cp_r);
    void removeAllNodes_helper(BSTNode<T> *&r);
    bool contains_helper(BSTNode<T> *r, BSTNode<T> *n) const;
    void insert_helper(BSTNode<T> *&r, const T &new_data);
    void remove_helper(BSTNode<T> *&r, const T &data);
    BSTNode<T> * search_helper(BSTNode<T> *r, const T &data) const;
    BSTNode<T> * pre_successor(BSTNode<T> *r, BSTNode<T> *node) const;
    BSTNode<T> * in_successor(BSTNode<T> *r, BSTNode<T> *node) const;
    BSTNode<T> * post_successor(BSTNode<T> *r, BSTNode<T> *node) const;
    T get_min(BSTNode<T> *r) const;

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

/* ********** Helper Functions START ********** */
template<class T>
void BST<T>::copy_helper(BSTNode<T> *&r, BSTNode<T> *cp_r){
    
    if (cp_r == NULL)
        return;
    
    r = new BSTNode<T>();
    r->data = cp_r->data;
    copy_helper(r->left,  cp_r->left);
    copy_helper(r->right, cp_r->right);
}


template<class T>
void BST<T>::removeAllNodes_helper(BSTNode<T> *&r){
    if (r == NULL){
        return;
    }
    else {
        BSTNode<T> *tmp = r;
        removeAllNodes_helper(r->left);
        removeAllNodes_helper(r->right);
        r = NULL;
        delete tmp;
    }
}

template<class T>
bool BST<T>::contains_helper(BSTNode<T> *r, BSTNode<T> *n) const{
    if (r == NULL)
        return false;
    if (r == n)
        return true;
    else if (r->data < n->data){
        return contains_helper(r->right, n);
    }
    else {
        return contains_helper(r->left, n);
    }
    
}

template<class T>
void BST<T>::insert_helper(BSTNode<T> *&r, const T &new_data){
    if (r == NULL){
        r = new BSTNode<T>(new_data, NULL, NULL);
        return;
    }

    if (r->data < new_data){
        insert_helper(r->right, new_data);
    }
    
    else{
        insert_helper(r->left, new_data);
    }
}


template<class T>
T BST<T>::get_min(BSTNode<T> *r) const{
    while (r->left) {
        r = r->left;
    }
    return r->data;
}

template<class T> 
void BST<T>::remove_helper(BSTNode<T> *&r, const T &data){
    if (r == NULL)
        return;
    
    if (r->data < data){
        remove_helper(r->right, data);
    }
    else if (r->data > data){
        remove_helper(r->left, data);
    }
    else {
        if (r->left != NULL && r->right != NULL){
            r->data = get_min(r->right);
            remove_helper(r->right, r->data);
        }
        else {
            BSTNode<T> *tmp = r;
            if (r->right != NULL) {
                r = r->right;
            }
            else {
                r = r->left;
            }
            delete tmp;
        }
    }

}

template<class T>
BSTNode<T> * BST<T>::search_helper(BSTNode<T> *r, const T &data) const{
    if (r == NULL)
        return NULL;
        
    if (r->data == data)
        return r;
    
    if (r->data < data){
        return search_helper(r->right, data);
    }
    else if (r->data > data){
        return search_helper(r->left, data);
    }
}

template<class T>
BSTNode<T> * BST<T>::pre_successor(BSTNode<T> *r, BSTNode<T> *node) const{
    if (!r || !node){
        return NULL;
    }

    BSTNode<T> * left_node;
    BSTNode<T> * right_node;

    left_node = pre_successor(r->left, node);
    right_node = pre_successor(r->right, node);

    if (left_node == node){
        if (right_node){
            return right_node;
        }
        else {
            return left_node;
        }
    }

    if (right_node == node){
        return right_node;
    }

    if (left_node != r->left){
        return left_node;
    }

    if (right_node != r->right){
        return right_node;
    }

    return r;

}


template<class T>
BSTNode<T> * BST<T>::in_successor(BSTNode<T> *r, BSTNode<T> *node) const{
    if (!r || !node){
        return NULL;
    }

    BSTNode<T> * left_node;
    BSTNode<T> * right_node;

    left_node = in_successor(r->left, node);
    right_node = in_successor(r->right, node);

    if (left_node && right_node){
        if (left_node->data > node->data){
            return left_node;
        }

        if (r->data > node->data){
            return r;
        }

        if (right_node->data > node->data){
            return right_node;
        }
    }

    if (left_node){
        if (left_node->data > node->data){
            return left_node;
        }
    }

    if (r->data > node->data){
        return r;
    }

    if (right_node){
        if (right_node->data > node->data){
            return right_node;
        }
    }

    return NULL;    

}

template<class T>
BSTNode<T> * BST<T>::post_successor(BSTNode<T> *r, BSTNode<T> *node) const{
    if (r == NULL || r == node)
        return NULL;

    if (r->right == node){
        return r;
    }

    if (r->left == node){
        BSTNode<T> *successor = r->right;
        if (!successor)
            return r;
        else {
            while (successor->left){
                successor = successor->left;
            }
            if (successor->right)
                return successor->right;
            else 
                return successor;
        }
    }

    if (r->data < node->data) {
        return post_successor(r->right, node);
    }
    else {
        return post_successor(r->left, node);
    }
}

/* ********** Helper Functions END ********** */

template<class T>
BST<T>::BST() {
    /* TODO */
    root = NULL;
}

template<class T>
BST<T>::BST(const BST<T> &obj) {
    /* TODO */
    if (obj.root == NULL){
        root = NULL;
    }
    else {
        copy_helper(root, obj.root);
    }

}

template<class T>
BST<T>::~BST() {
    /* TODO */
    removeAllNodes_helper(root);
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    /* TODO */
    return root;
}

template<class T>
bool BST<T>::isEmpty() const {
    /* TODO */
    return !root;
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    /* TODO */
    return contains_helper(root, node);
}

template<class T>
void BST<T>::insert(const T &data) {
    /* TODO */
    insert_helper(root, data);
}

template<class T>
void BST<T>::remove(const T &data) {
    /* TODO */
    remove_helper(root, data);
}

template<class T>
void BST<T>::removeAllNodes() {
    /* TODO */
    removeAllNodes_helper(root);
}

template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    /* TODO */
    return search_helper(root, data);
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {
    BSTNode<T> *successor;

    if (tp == inorder) {
        /* TODO */
        if (node->right){
            successor = node->right;
            while (successor->left){
                successor = successor->left;
            }
            return successor;
        }
        else{
            successor = in_successor(root, node);
            if (successor != node){
                return successor;
            }
            else{
                return NULL;
            }
        }
    } 
    
    else if (tp == preorder) {
        /* TODO */

        if (node->left){
            return node->left;
        }

        if (node->right){
            return node->right;
        }

        successor = pre_successor(root, node);
        if (successor != node)
            return successor;
        else
            return NULL;
    } 
    
    else if (tp == postorder) {
        /* TODO */
        successor = post_successor(root, node);
        return successor;
    }
    
    return NULL;
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;                
    } else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;        
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */
    if (this != &rhs){
        removeAllNodes_helper(root);
        if (&rhs == NULL){
            return *this;
        }

        copy_helper(root, rhs.root);
    }
    return *this;
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        /* TODO */
        std::cout << "\t" << node->data;

        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);

        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
         

    } else if (tp == postorder) {
        /* TODO */
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }

        std::cout << "\t" << node->data;

    }
}
