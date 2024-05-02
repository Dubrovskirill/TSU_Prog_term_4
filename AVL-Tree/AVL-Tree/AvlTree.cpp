#include "AvlTree.h"
BinaryTree::Node* AvlTree::_addNode(Node* root, const int key){

    if (!root) {
        root = new Node(key);
        isFixed = false;
    }
    else if (key < root->getKey()) {
        root->setLeft(_addNode(root->getLeft(), key));
        
        if (!isFixed) {
            root->setBalance(root->getBalance() - 1);
            balanceAfterAdd(root);
        }
    }
    else if (key > root->getKey()) {
        root->setRight(_addNode(root->getRight(), key));
        
        if (!isFixed) {
            root->setBalance(root->getBalance() + 1);
            balanceAfterAdd(root);
        }
    }

    return root;
}

int AvlTree::bFactor(Node* node) const {

    return height(node->getRight()) - height(node->getLeft());
}

void AvlTree::balanceAfterAdd(Node*& root) {

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
   bottom->setBalance(0);
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
    bottom->setBalance(0);
    return bottom;
}

BinaryTree::Node* AvlTree::turnDoubleRL(Node* middle, Node* top) {
    if (!middle || !middle->getRight() || !middle->getRight()->getLeft()) 
        return{};
    
    Node* bottom = middle->getRight();
    bottom = turnRight(bottom, middle);
    bottom->setBalance(bottom->getBalance() + 1);
    middle = turnLeft(middle, top);
    return middle;

  
    
   
}

BinaryTree::Node* AvlTree::turnDoubleLR(Node* middle, Node* top) {

    if (!middle || !middle->getLeft() || !middle->getLeft()->getRight())
        return{};
    Node* bottom = middle->getLeft();
    bottom = turnLeft(bottom, middle);
    bottom->setBalance(bottom->getBalance()+1);
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

bool AvlTree::remove(const int key) {
    
    Node* node = find(key);
    if (!node)
        return false;

    if (size() == 1) {
        delete node;
        m_root = nullptr;
        return true;
    }

    Node* root=m_root, *replacement;
    
    std::list < BinaryTree::Node*> route;
    if (node->getRight() && node->getLeft()) {
        replacement = findReplacement(node);
        root = parent(replacement);
        if (node == root) {
            root = replacement;
        }
    }
    else {
        root = parent(node);
        if (root == node) {
            root = (root->getLeft() ? root->getLeft() : root->getRight());
        }
    }
    if (SearchTree::remove(key)) {
        isFixed = false;
        formRoute(route, m_root, root);
    }

    return isFixed==false 
        ? avlRemove(route)
        :isFixed;
    
}

void AvlTree::formRoute(std::list < BinaryTree::Node*>& route, Node* from, Node* to)
{ 
    route.push_back(from);
    if (from->getKey() > to->getKey())
        formRoute(route, from->getLeft(), to);
    else  if (from->getKey() < to->getKey())
        formRoute(route, from->getRight(), to);
    return;
}

bool AvlTree::avlRemove(std::list < BinaryTree::Node*>& route)
{
   balanceAfterRemove(*(--route.end()));
   route.pop_back();
   if (!isFixed && !route.empty())
       avlRemove(route);
   return isFixed;
}


void AvlTree::balanceAfterRemove(Node*& root) {
    

    Node* p = parent(root);
    if (p == root)
        p = nullptr;
    
    switch (bFactor(root)) {
    case 1:
        isFixed = true;
        break;

    case -1:
        isFixed = true;
        break;

    case -2:
        if (bFactor(root->getLeft()) < 1) {
            root = turnRight(root, p);
        }
        else {
            root = turnDoubleLR(root, p);
        }
        break;

    case 2:
        if (bFactor(root->getRight()) > -1) {
            root = turnLeft(root, p);
        }
        else {
            root = turnDoubleRL(root, p);
        }
        break;

    default:
        break;

    }
}





