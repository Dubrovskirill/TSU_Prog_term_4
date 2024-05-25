#pragma once
#include<stack>

#include"../../BinarySearchTree/SearchTree.h"
class AvlTree : public SearchTree
{
public:
    AvlTree() = default;
    ~AvlTree() = default;

    AvlTree copy() const;
    AvlTree copy(Node* root) const;
    AvlTree& operator = (const AvlTree& other) = default;
    bool isFixed = true;
     bool remove(const int & key) override;
protected:
    Node* _addNode(Node* root, const int key) override;
    Node* _addNodeAvl(Node* parent, Node* root, const int key);
    int bFactor(Node* node) const;
    void balanceCorrection(Node* parent, Node*& root, bool addOrRem=false); // false - add,  true -  remove;
    Node* turnRight(Node* middle, Node* top);
    Node* turnLeft(Node* middle, Node* top);
    Node* turnDoubleRL(Node* middle, Node* top);
    Node* turnDoubleLR(Node* middle, Node* top);

    bool removeRecursive(Node* parent, Node* root, const int& key) override;
    bool removeNodeWithTwoChildren(Node* node) override;
    void route(Node* parent,Node* from, Node* to);


private:
   
    bool isRemove = true;
    
};


