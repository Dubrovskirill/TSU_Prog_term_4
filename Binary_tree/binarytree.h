#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <vector>
#include <list>
#include <windows.h>



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

   int min() const;
   int max() const;
   std::vector<int> TreeToVector()const;
   void printHorizontal(Node *root, int marginLeft, int levelSpacing) const;
   void printHorizontal() const;
   void print(Node *root, int leftBorderPos=10, int rightBorderPo=100, int yPos=10) const;
   void print() const;
   void moveCursor(int xPos, int yPos ) const;
   void printLeafs() const;
   std::vector<Node*> leafsVector() const;
   int level(const int key) const;
   int level(Node* root, const int key, int currentLevel) const;
   bool remove(const int key);
   bool removeRootNode();
   bool removeLeafNode(Node* node);
   bool removeNodeWithTwoChildren(Node* node);
   bool removeNodeWithOneChild(Node* node);
   Node* findReplacementNode();
   void getLeafs(Node* node, std::vector<Node*>& leafs);
   Node* parent(const Node* child) const;

   BinaryTree& operator=(const BinaryTree& other);


protected:
   virtual BinaryTree::Node* _addNode(Node* root, const int key);
private:
   std::vector<BinaryTree::Node*> _leafs(Node* root) const;
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
