#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <vector>
#include <list>



class BinaryTree
{

class Node;
public:
   BinaryTree() = default;
   BinaryTree(const BinaryTree& other);
   ~BinaryTree() {clear();}
   void clearChildren(Node *root);
   void clear();
   void TreeToList(std::list<Node*>& nodeList) const;
   Node* copy(Node* root) const;
   Node* copy() const;

private:
    Node* m_root = nullptr;

};



class BinaryTree::Node {
    friend class BinaryTree;
public:
    Node(const int key = 0, Node* left = nullptr, Node* right = nullptr)
        : m_key(key), m_left(left), m_right(right)
    {}
    ~Node() = default;
    int key() const;
    int getKey() const;
    void setKey(int key);
    Node* getLeft();
    Node* getRight();
    void setLeft(Node* left);
    void setRight(Node* right);


private:
    int m_key = 0;
    Node* m_left = nullptr;
    Node* m_right = nullptr;

};


#endif // BINARYTREE_H
