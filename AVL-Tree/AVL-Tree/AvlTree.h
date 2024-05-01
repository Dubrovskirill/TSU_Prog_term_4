#pragma once
#include"../../BinarySearchTree/SearchTree.h"
class AvlTree : public SearchTree
{
public:
    AvlTree() = default;
    ~AvlTree() = default;
    
protected:
    Node* _addNode(Node* root, const int key) override;
    int bFactor(Node* node);
    void balance(Node*& root, Node* nodeSide);
    Node* turnRight(Node* middle, Node* top);
    Node* turnLeft(Node* middle, Node* top);
    Node* turnDoubleRL(Node* middle, Node* top);
    Node* turnDoubleLR(Node* middle, Node* top);

private:
   
    bool isFixed = false;
    
};

