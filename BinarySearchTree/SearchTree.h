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


};

#endif // SEARCHTREE_H
