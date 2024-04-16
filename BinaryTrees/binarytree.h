#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <vector>
#include <list>




class BinaryTree
{


public:
   class Node;
   BinaryTree() = default;
   BinaryTree(const BinaryTree& other);
   ~BinaryTree() {clear();}

   void clearChildren(Node *root);
   void clear();

   int size() const;
   int min() const;
   int max() const;
   int height() const;
   int height(Node* root) const;
   int nodeCount() const;
   int level(const int key) const;
   int level(Node* root, const int key, int currentLevel) const;

   BinaryTree copy(Node *root) const;
   BinaryTree copy() const;
   bool isBalanced() const;
   bool isBalanced(Node* root) const;
   bool isEmpty() const;
  
   Node* root() const;
   Node* find(const int key) const;
   Node* parent(const Node* child) const;
   virtual Node* find(Node* root, const int key) const;
   virtual Node* add(const int key);
   bool remove(const int key);

   void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
   void printHorizontal() const;
   void print(Node* root, int leftBorderPos = 10, int rightBorderPo = 100, int yPos = 10) const;
   void print() const;
   void moveCursor(int xPos, int yPos) const;
   void printLeafs() const;
   void getLeafs(Node* node, std::vector<Node*>& leafs);
   void nodeList(std::list<Node*>& nodeList) const;
   std::vector<int> keysVector()const;
   std::vector<Node*> leafsVector() const;

   BinaryTree& operator=(const BinaryTree& other);
  
   
   void print_2(Node* root,int level, int xPos, int yPos, int xShift) const;
   void print_2(Node* root) const;
  
   void printSpaces(int count);
   void print_3(Node* root);


   
private:
    bool removeRootNode(Node* node);
    bool removeLeafNode(Node* node);
    bool removeNodeWithTwoChildren(Node* node);
    bool removeNodeWithOneChild(Node* node);

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
