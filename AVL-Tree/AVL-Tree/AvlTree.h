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

protected:
    Node* _addNode(Node* root, const int key) override;
    int bFactor(Node* node) const;
    void balance—orrection(Node*& root, bool flag=false);
    Node* turnRight(Node* middle, Node* top);
    Node* turnLeft(Node* middle, Node* top);
    Node* turnDoubleRL(Node* middle, Node* top);
    Node* turnDoubleLR(Node* middle, Node* top);

    bool removeRecursive(Node* root, const int key) override;
    bool removeNodeWithTwoChildren(Node* node) override;
    void route(Node* from, Node* to);

private:
    struct routeNode;
    bool isFixed = true; 
};

struct AvlTree::routeNode
{
    Node * node= nullptr;
    int balance = 0;
};

