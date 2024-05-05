#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include "../BinaryTrees/binarytree.h"
class SearchTree: public BinaryTree
{
public:
    SearchTree() = default;
    SearchTree(const SearchTree& other)
        : BinaryTree(other) {}
    ~SearchTree() = default;



    SearchTree copy() const;
    SearchTree copy(Node* root) const;

    Node* find(const int key) const;
    Node* find(Node* root, const int key) const override;

    int min() const override;
    int max() const override;
    int level(const int key) const;
    int level(Node* root, const int key, int currentLevel) const override;

    std::vector<int> keysVector() const;
    std::vector<int> keysVector(Node* root, std::vector<int>& keys)const;

    SearchTree& operator = (const SearchTree& other) = default;

   // bool remove(const int key) override;


protected:
    Node* _addNode(Node* root, const int key) override;
    BinaryTree::Node* findReplacement(Node* root) const;

    bool removeRecursive(Node* root, const int key) override;
    bool removeLeafNode(Node* node) override;
    bool removeNodeWithOneChild(Node* node) override;
    bool removeNodeWithTwoChildren(Node* node) override;
};

#endif // SEARCHTREE_H
