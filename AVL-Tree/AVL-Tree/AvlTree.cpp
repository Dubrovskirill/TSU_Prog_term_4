#include "AvlTree.h"
#include<stack>
BinaryTree::Node* AvlTree::_addNode(Node* root, const int key){

    if (!root) {
        root = new Node(key);
        isFixed = false;
        return root;
    }
    else if (key < root->getKey()) {
        root->setLeft(_addNode(root->getLeft(), key));
        
        if (!isFixed) {
            root->setBalance(root->getBalance() - 1);
            balance—orrection(root);
        }
    }
    else if (key > root->getKey()) {
        root->setRight(_addNode(root->getRight(), key));
        
        if (!isFixed) {
            root->setBalance(root->getBalance() + 1);
            balance—orrection(root);
        }
    }
   if(root==m_root)
       isFixed = true;
    return root;
}

int AvlTree::bFactor(Node* node) const {

    return height(node->getRight()) - height(node->getLeft());
}

void AvlTree::balance—orrection(Node*& root,bool flag) {

    Node* p = parent(root);
    if (p == root)
        p = nullptr;

    switch (root->getBalance()) {
    case 0:
        isFixed = true;
        break;

    case -2:
        if (root->getLeft()->getBalance() < 1) {
            root = turnRight(root, p);
        }
        else {
            root = turnDoubleLR(root, p);
        }
        isFixed = true;
        break;


    case 2:
        if (root->getRight()->getBalance() > -1) {
            root = turnLeft(root, p);
        }
        else {
            root = turnDoubleRL(root, p);
        }
        isFixed = true;
        break;
    
    case 1:
        if (flag == true)
            isFixed = true;
        break;

    case -1:
        if (flag == true)
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


    middle->setLeft(bottom->getRight());
    bottom->setRight(middle);
    if (!top) 
        m_root = bottom;
    else if (top->getLeft() == middle)
        top->setLeft(bottom);
    else
        top->setRight(bottom);

   middle->setBalance(bFactor(middle));
   bottom->setBalance(bFactor(bottom));
    return bottom;
}

BinaryTree::Node* AvlTree::turnLeft(Node* middle, Node* top) {

    if (!middle || !middle->getRight()) 
        return{};
    
    Node* bottom = middle->getRight();

    
    middle->setRight(bottom->getLeft());
    bottom->setLeft(middle);

    if (!top)
        m_root = bottom;
    else if (top->getLeft() == middle)
        top->setLeft(bottom);
    else
        top->setRight(bottom);
    middle->setBalance(bFactor(middle));
    bottom->setBalance(bFactor(bottom));
    return bottom;
}

BinaryTree::Node* AvlTree::turnDoubleRL(Node* middle, Node* top) {
    if (!middle || !middle->getRight() || !middle->getRight()->getLeft()) 
        return{};
    
    Node* bottom = middle->getRight();
    bottom = turnRight(bottom, middle);
    //bottom->setBalance(bottom->getBalance() + 1);
    middle = turnLeft(middle, top);
    return middle;

  
    
   
}

BinaryTree::Node* AvlTree::turnDoubleLR(Node* middle, Node* top) {

    if (!middle || !middle->getLeft() || !middle->getLeft()->getRight())
        return{};
    Node* bottom = middle->getLeft();
    bottom = turnLeft(bottom, middle);
    //bottom->setBalance(bottom->getBalance()+1);
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



bool AvlTree::removeRecursive(Node* root, const int key)
{
    if (!root)
        return false;

    if (root->getKey() == key) {

        if (!root->getLeft() && !root->getRight()) {
            removeLeafNode(root);
            return isFixed = false;
        }
        else if (!root->getLeft() || !root->getRight()) {
            removeNodeWithOneChild(root);
            return isFixed = false;
        }
        else {
            return removeNodeWithTwoChildren(root);
        }

    }
    else if (root->getKey() > key) {
        removeRecursive(root->getLeft(), key);
        if (!isFixed) {
            root->m_balance += 1;
            balance—orrection(root, true);
        }
    }
    else {
        removeRecursive(root->getRight(), key);
        if (!isFixed) {
            root->m_balance -= 1;
            balance—orrection(root, true);
        }
    }
    return isFixed;
}

bool AvlTree::removeNodeWithTwoChildren(Node* node) {
   

    Node* replacementNode = findReplacement(node);
    Node* parentReplacementNode = parent(replacementNode);
    replacementNode->setRight(node->getRight());
     
    if (parentReplacementNode != node)
    {
        parentReplacementNode->setRight(replacementNode->getLeft());
        replacementNode->setLeft(node->getLeft());
    }

    if (m_root == node) {
        m_root = replacementNode;
        parentReplacementNode = m_root;
        m_root->m_balance = bFactor(m_root);
    }
    else {
        parentReplacementNode = parent(node);
        if (parentReplacementNode)
        {
            if (parentReplacementNode->getLeft() == node)
                parentReplacementNode->setLeft(replacementNode);
            else
                parentReplacementNode->setRight(replacementNode);
        }

    }

    isFixed = false;
    route(m_root, parentReplacementNode);
    return isFixed;
}

void AvlTree::route(Node* from, Node* to)
{
    if (from->getKey() > to->getKey()) {
        route(from->getLeft(), to);
        if (!isFixed) {
            from->m_balance += 1;
            balance—orrection(from, true);
        }
    }
    else  if (from->getKey() < to->getKey()) {
        route(from->getRight(), to);
        if (!isFixed) {
            from->m_balance -= 1;
            balance—orrection(from, true);
        }
    }
    else {
        balance—orrection(from, true);
    }
    return;
}






