#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include "../../BinaryTrees/binarytree.h"
class SearchTree: public BinaryTree
{
public:
    SearchTree() = default;
    ~SearchTree() = default;

    Node* add(Node* root, const int value);

    SearchTree copy(Node* root) const;
    SearchTree copy() const;

    Node* find(const int key) const;
    Node* find(Node* root, const int key) const;

    int min() const;
    int max() const;


};

#endif // SEARCHTREE_H
