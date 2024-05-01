#pragma once
#include"../../BinarySearchTree/SearchTree.h"
class AvlTree : public SearchTree
{
public:
    AvlTree() = default;
    ~AvlTree() = default;

    AvlTree copy() const;
    AvlTree copy(Node* root) const;
    AvlTree& operator = (const AvlTree& other) = default;
    bool remove(const int key) override;
protected:
    Node* _addNode(Node* root, const int key) override;
    int bFactor(Node* node) const;
    void balanceAfterAdd(Node*& root, Node* nodeSide);
    Node* turnRight(Node* middle, Node* top);
    Node* turnLeft(Node* middle, Node* top);
    Node* turnDoubleRL(Node* middle, Node* top);
    Node* turnDoubleLR(Node* middle, Node* top);

    bool avlRemove(std::list < BinaryTree::Node*>& route);
    void balanceAfterRemove(Node*& root);
    void formRoute(std::list < BinaryTree::Node*>& route, Node* from, Node* to);

private:
   
    bool isFixed = false; 
};

