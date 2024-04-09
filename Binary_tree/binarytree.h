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
   BinaryTree copy(Node *root) const;
   BinaryTree copy() const;
   bool isBalanced() const;
   bool isBalanced(Node* root) const;
   bool isEmpty() const;
   int height() const;
   int height(Node* root) const;
   int nodeCount() const;
   Node* root() const;
   virtual Node* add(const int key);
   Node* find(const int key) const;
   virtual Node* find(Node* root, const int key) const;

protected:
   virtual BinaryTree::Node* _addNode(Node* root, const int key);
private:

   Node* _copy(Node* root) const;
   Node* _copy() const;
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
