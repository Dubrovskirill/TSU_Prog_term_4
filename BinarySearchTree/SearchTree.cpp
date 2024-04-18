#include "SearchTree.h"
#include "../../BinaryTrees/binarytree.h"

BinaryTree::Node* SearchTree::add(Node* root, const int value) {
    if(!root) {
        root = new Node(value);
    } else if(value < root->getKey()) {
        root->setLeft(add(root->getLeft(), value));
    } else if(value > root->getKey()){
        root->setRight(add(root->getRight(), value));
    }

}

SearchTree SearchTree::copy() const {
    return copy(m_root);
}

SearchTree SearchTree::copy(Node* root) const {
    BinaryTree tempTree = BinaryTree::copy();
    SearchTree newSearchTree;
    newSearchTree.m_root = _copy(tempTree.root());
    return newSearchTree;
}

BinaryTree::Node* SearchTree::find(const int key) const {
    return find(root(), key);
}

BinaryTree::Node* SearchTree::find(Node* root, const int key) const {
    if (root == nullptr || root->getKey() == key) {
        return root;
    }
    if (key < root->getKey()) {
        return find(root->getLeft(), key);
    }
    return find(root->getRight(), key);
}

int SearchTree::min() const {
    if (isEmpty())
        return INT_MIN;

    Node* current = root();
    while (current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    return current->getKey();
}

int SearchTree::max() const {
    if (isEmpty())
        return INT_MIN;

    Node* current = root();
    while (current->getRight() != nullptr) {
        current = current->getRight();
    }
    return current->getKey();
}
