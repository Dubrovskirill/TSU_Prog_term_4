#include "AvlTree.h"
BinaryTree::Node* AvlTree::_addNode(Node* root, const int key){

    if (!root) {
        root = new Node(key);
        isFixed = false;
    }
    else if (key < root->getKey()) {
        root->setLeft(_addNode(root->getLeft(), key));
        if (!isFixed) {
            balance(root, root->getLeft());
        }
    }
    else if (key > root->getKey()) {
        root->setRight(_addNode(root->getRight(), key));
        if (!isFixed) {
            balance(root, root->getRight());
        }
    }

    return root;
}

int AvlTree::bFactor(Node* node) {

    return height(node->getRight()) - height(node->getLeft());
}

void AvlTree::balance(Node*& root, Node* nodeChild) {

    if (nodeChild == root) {
        return;
    }

    Node* p = parent(root);
    if (p == root)
        p = nullptr;

    switch (bFactor(root)) {
    case 0:
        isFixed = true;
        break;

    case -2:
        if (bFactor(nodeChild) < 1) {
            root = turnRight(root, p);
        }
        else {
            root = turnDoubleLR(root, p);
        }
        isFixed = true;
        break;


    case 2:
        if (bFactor(nodeChild) > -1) {
            root = turnLeft(root, p);
        }
        else {
            root = turnDoubleRL(root, p);
        }
        isFixed = true;
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
    return bottom;
}

BinaryTree::Node* AvlTree::turnDoubleRL(Node* middle, Node* top) {
    if (!middle || !middle->getRight() || !middle->getRight()->getLeft()) 
        return{};
    
    Node* bottom = middle->getRight();
    Node* extra = bottom->getLeft();

    bottom->setLeft(extra->getRight());
    extra->setRight(bottom);

    middle->setRight(extra->getLeft());
    extra->setLeft(middle);
    if (!top) 
        m_root=extra;
    else if (top->getLeft() == middle)
        top->setLeft(extra);
    else
        top->setRight(extra);
    
    return extra;
}

BinaryTree::Node* AvlTree::turnDoubleLR(Node* middle, Node* top) {

    if (!middle || !middle->getLeft() || !middle->getLeft()->getRight())
        return{};

    Node* bottom = middle->getLeft();
    Node* extra = bottom->getRight();

    bottom->setRight(extra->getLeft());
    extra->setLeft(bottom);

    middle->setLeft(extra->getRight());
    extra->setRight(middle);
    if (!top)
        m_root = extra;
    else if (top->getLeft() == middle)
        top->setLeft(extra);
    else
        top->setRight(extra);

    return extra;
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