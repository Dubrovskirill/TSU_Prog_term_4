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
    int level(const int key) const;
    int level(Node* root, const int key, int currentLevel) const;

    std::vector<int> keysVector() const;
    std::vector<int> keysVector(Node* root, std::vector<int>& keys)const;
    SearchTree& operator=(const SearchTree& other);

};

#endif // SEARCHTREE_H
