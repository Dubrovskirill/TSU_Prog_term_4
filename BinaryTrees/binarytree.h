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
   virtual int min() const;
   virtual int max() const;
   int height() const;
   int height(Node* root) const;
   int nodeCount() const;
   int level(const int key) const;
   virtual int level(Node* root, const int key, int currentLevel) const;

   BinaryTree copy(Node *root) const;
   BinaryTree copy() const;
   bool isBalanced() const;
   bool isBalanced(Node* root) const;
   bool isEmpty() const;
  
   Node* root() const;
  
   Node* find(const int key) const;
   Node* parent(const Node* child) const;
   virtual Node* find(Node* root, const int key) const;
   Node* add(const int key);
  
   void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
   void printHorizontal() const;
   void print(Node* root, int leftBorderPos = 10, int rightBorderPos = 100, int yPos = 0) const;
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
   void printSpaces(int count) const;
   void print_3(Node* root) const;
   

   std::vector<int> bypassLnr()const;

   virtual bool remove(const int key);
protected:
    
    virtual bool removeRecursive(Node* root, const int key);
    virtual bool removeRootNode(Node* node);
    virtual bool removeLeafNode(Node* node);
    virtual bool removeNodeWithOneChild(Node* node);
    virtual bool removeNodeWithTwoChildren(Node* node);

protected:
   virtual BinaryTree::Node* _addNode(Node* root, const int key);
   Node* _copy(Node* root) const;
   void _bypassLRR(Node* root, std::vector<int>& keys)const;
   Node* m_root = nullptr;
private:
   std::vector<BinaryTree::Node*> _leafs(Node* root) const;
   Node* _copy() const;


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

    int getBalance() const { return m_balance; }
    void setBalance(int newB) { m_balance = newB; }
    int m_balance = 0;
private:
    
private:
   
    int m_key = 0;
    Node* m_left = nullptr;
    Node* m_right = nullptr;

    
};


#endif // BINARYTREE_H
