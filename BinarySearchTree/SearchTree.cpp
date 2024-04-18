#include "SearchTree.h"
#include "../../BinaryTrees/binarytree.h"

BinaryTree::Node* SearchTree::add(Node* root, const int value)
{
    if(!root) {
        root = new Node(value);
    } else if(value < root->getKey()) {
        root->setLeft(add(root->getLeft(), value));
    } else if(value > root->getKey()){
        root->setRight(add(root->getRight(), value));
    }

}

SearchTree SearchTree::copy() const
{
    return copy(m_root);
}

SearchTree SearchTree::copy(Node* root) const
{
    BinaryTree tempTree = BinaryTree::copy();
    SearchTree newSearchTree;
    newSearchTree.m_root = _copy(tempTree.root());
    return newSearchTree;
}
