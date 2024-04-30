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
private:

    bool isFixed = false;
    
};

