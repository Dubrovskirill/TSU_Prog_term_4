#include "binarytree.h"
#include "ui_binarytree.h"

BinaryTree::BinaryTree(const BinaryTree& other)
{
    m_root = other.copy();
}

BinaryTree::Node* BinaryTree::copy() const
{
    return copy(m_root);
}

BinaryTree::Node* BinaryTree::copy(Node* root) const
{
    Node* cloneRoot = nullptr;
    if (!root)
        return cloneRoot;
    cloneRoot = new Node(root->getKey());
    cloneRoot->setLeft(copy(root->getLeft()));
    cloneRoot->setRight(copy(root->getRight()));
    return cloneRoot;
}

void BinaryTree::clearChildren(Node *root)
{
    if (!root)
        return;
    std::list<Node*> listForClearNode;
    if(root->getLeft())
        listForClearNode.push_back(root->getLeft());
    if (root->getRight())
        listForClearNode.push_back(root->getRight());
    TreeToList(listForClearNode);
    while (!listForClearNode.empty())
    {
        delete listForClearNode.back();
        listForClearNode.pop_back();
    }
    root->setLeft(nullptr);
    root->setRight(nullptr);
}

void BinaryTree::clear()
{
    clearChildren(m_root);
    delete m_root;
    m_root = nullptr;
}
void BinaryTree::TreeToList(std::list<Node*>& nodeList) const
{
    Node* current = nullptr;
    std::list<Node*> tmp;
    tmp = nodeList;
    while (!tmp.empty())
    {
        if(tmp.front())
        {
            current = tmp.front();
            if(current->getLeft()){
                nodeList.push_back(current->getLeft());
                tmp.push_back(current->getLeft());
            }
            if(current->getRight()){
                nodeList.push_back(current->getRight());
                tmp.push_back(current->getRight());
            }
        }
        tmp.pop_front();
    }
}


int BinaryTree::Node::getKey() const
{
    return m_key;
}

void BinaryTree::Node::setKey(int key)
{
    m_key = key;
}

BinaryTree::Node* BinaryTree::Node::getLeft()
{
    return m_left;
}

BinaryTree::Node* BinaryTree::Node::getRight()
{
    return m_right;
}

void BinaryTree::Node::setLeft(Node* left)
{
    m_left = left;
}

void BinaryTree::Node::setRight(Node* right)
{
    m_right = right;
}

