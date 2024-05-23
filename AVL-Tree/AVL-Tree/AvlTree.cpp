#include "AvlTree.h"
#include<stack>
#include <queue>
#include <chrono>
BinaryTree::Node* AvlTree::_addNode(Node* root, const int key){

    return _addNodeAvl(m_root, root, key);
}
BinaryTree::Node* AvlTree::_addNodeAvl(Node* parent, Node* root, const int key) {

    if (!root) {
        root = new Node(key);
        isFixed = false;
        return root;
    }
    else if (key < root->getKey()) {
        root->setLeft(_addNodeAvl(root, root->getLeft(), key));

        if (!isFixed) {
            root->setBalance(root->getBalance() - 1);

            balanceCorrection(parent, root);

        }
    }
    else if (key > root->getKey()) {
        root->setRight(_addNodeAvl(root, root->getRight(), key));

        if (!isFixed) {
            root->setBalance(root->getBalance() + 1);

            balanceCorrection(parent, root);

        }
    }
    if (root == m_root)
        isFixed = true;
    return root;
}
int AvlTree::bFactor(Node* node) const {

    return height(node->getRight()) - height(node->getLeft());
}

void AvlTree::balanceCorrection(Node* parent, Node*& root,bool addOrRem) {
   
    if (parent == root)
        parent = nullptr;

   
    switch (root->getBalance()) {
    case 0:
        if (!addOrRem)
            isFixed = true;
        break;

    case -2:
        if (root->getLeft()->getBalance() < 1) {
            root = turnRight(root, parent);
        }
        else {
            root = turnDoubleLR(root, parent);
        }
        
         parent = this->parent(root);
         balanceCorrection(parent,root, addOrRem);
       
        break;


    case 2:
        if (root->getRight()->getBalance() > -1) {
            root = turnLeft(root, parent);
        }
        else {
            root = turnDoubleRL(root, parent);
        }
       

        parent = this->parent(root);
        balanceCorrection(parent,root, addOrRem);
        

        break;
    
    case 1:
        if (addOrRem)
            isFixed = true;
        break;

    case -1:
        if (addOrRem)
            isFixed = true;
        break;
        
    default:
        break;
    }

}

BinaryTree::Node* AvlTree::turnRight(Node* middle, Node* top) {

    if (!middle || !middle->getLeft()) 
        return{};
    
    Node* bottom = middle->getLeft();

    if (!top) 
        m_root = bottom;
    else if (top->getLeft() == middle)
        top->setLeft(bottom);
    else
        top->setRight(bottom);
    middle->setLeft(bottom->getRight());
    bottom->setRight(middle);

    middle->setBalance(middle->getBalance() + 1 + std::max(0, -bottom->getBalance()));
    bottom->setBalance(bottom->getBalance() + 1 + std::max(0, middle->getBalance()));
  
   
    return bottom;
}

BinaryTree::Node* AvlTree::turnLeft(Node* middle, Node* top) {

    if (!middle || !middle->getRight()) 
        return{};
    
    Node* bottom = middle->getRight();

    if (!top)
        m_root = bottom;
    else if (top->getLeft() == middle)
        top->setLeft(bottom);
    else
        top->setRight(bottom);

    middle->setRight(bottom->getLeft());
    bottom->setLeft(middle);

    middle->setBalance(middle->getBalance() - 1 - std::max(0, bottom->getBalance()));
    bottom->setBalance(bottom->getBalance() - 1 - std::max(0, -middle->getBalance()));
    return bottom;
}

BinaryTree::Node* AvlTree::turnDoubleRL(Node* middle, Node* top) {
    if (!middle || !middle->getRight() || !middle->getRight()->getLeft()) 
        return{};
    
    Node* bottom = middle->getRight();
    turnRight(bottom, middle);
    middle = turnLeft(middle, top);
    return middle;

  
    
   
}

BinaryTree::Node* AvlTree::turnDoubleLR(Node* middle, Node* top) {

    if (!middle || !middle->getLeft() || !middle->getLeft()->getRight())
        return{};
    Node* bottom = middle->getLeft();
    turnLeft(bottom, middle);
    middle = turnRight(middle, top);
    return middle;

}

AvlTree AvlTree::copy() const
{
    return copy(m_root);
}

AvlTree AvlTree::copy(Node* root) const
{
    BinaryTree temp = BinaryTree::copy(root);
    AvlTree tr;
    tr.m_root = _copy(temp.root());
    return tr;
}


bool AvlTree::remove(const int& key)
{
    
    return (removeRecursive(m_root,m_root, key) ? isFixed = true : false); 
}

bool AvlTree::removeRecursive(Node* parent, Node* root, const int& key)
{
    if (!root)
        return isRemove=false;

    if (root->getKey() == key) {

        if (!root->getLeft() && !root->getRight()) {
            isRemove=removeLeafNode(root);
            isFixed = false;
            return isRemove;
        }
        else if (!root->getLeft() || !root->getRight()) {
            isRemove=removeNodeWithOneChild(root);
            isFixed = false;
            return isRemove;
        }
        else {
            return isRemove=removeNodeWithTwoChildren(root);
        }

    }
    else if (root->getKey() > key) {
        removeRecursive(root,root->getLeft(), key);
        if (!isFixed) {
            root->m_balance += 1;
            balanceCorrection(parent,root, true);
        }
    }
    else {
        removeRecursive(root, root->getRight(), key);
        if (!isFixed) {
            root->m_balance -= 1;
            balanceCorrection(parent,root, true);
        }
    }
    
    return isRemove;
}

bool AvlTree::removeNodeWithTwoChildren(Node* node) {
   

    Node* replacementNode = findReplacement(node);
    Node* parentReplacementNode = parent(replacementNode);
    replacementNode->setRight(node->getRight());
     
    if (parentReplacementNode != node)
    {
        parentReplacementNode->setRight(replacementNode->getLeft());
        replacementNode->setLeft(node->getLeft());
        parentReplacementNode->setBalance(parentReplacementNode->getBalance() - 1);
    }

    if (m_root == node) {
        m_root = replacementNode;
       
    }
    else {
        Node* parentNode = parent(node);
        if (parentNode)
        {
            if (parentNode->getLeft() == node)
                parentNode->setLeft(replacementNode);
            else
                parentNode->setRight(replacementNode);
        }
        parentNode = replacementNode;
        
        
    }

    isFixed = false;
    replacementNode->m_balance = node->m_balance;
    if (parentReplacementNode == node){
        replacementNode->m_balance += 1;
    }
  
    
    route(m_root,m_root, (parentReplacementNode==node ? replacementNode : parentReplacementNode));
    
    delete node;
    return isFixed=true;
}

void AvlTree::route(Node* parent,Node* from, Node* to)
{
    if (from->getKey() > to->getKey()) {
        route(from,from->getLeft(), to);
        if (!isFixed) {
            from->m_balance += 1;
            balanceCorrection(parent,from, true);
        }
    }
    else  if (from->getKey() < to->getKey()) {
        route(from, from->getRight(), to);
        if (!isFixed) {
            from->m_balance -= 1;
            balanceCorrection(parent,from, true);
        }
    }
    else {
        balanceCorrection(parent,from, true);
    }
    return;
}







