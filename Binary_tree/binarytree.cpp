#undef max
#include "binarytree.h"

#include <algorithm>
#include <list>
#include <vector>
#include <iostream>

#include <windows.h>

BinaryTree::BinaryTree(const BinaryTree& other)
{
    m_root = other._copy();
}

BinaryTree BinaryTree::copy() const
{
    return copy(m_root);
}

BinaryTree BinaryTree::copy(Node* root) const
{
    if (!root)
        return *this;
    BinaryTree cloneTree;
    cloneTree.m_root = _copy(root);
    return cloneTree;
}

BinaryTree::Node* BinaryTree::_copy() const
{
    return _copy(m_root);
}

BinaryTree::Node* BinaryTree::_copy(Node* root) const
{
    Node* cloneRoot = nullptr;
    if (!root)
        return cloneRoot;
    cloneRoot = new Node(root->getKey());
    cloneRoot->setLeft(_copy(root->getLeft()));
    cloneRoot->setRight(_copy(root->getRight()));
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

bool BinaryTree::isBalanced() const
{
    return isBalanced(m_root);
}

bool BinaryTree::isBalanced(Node* root) const
{
    if (!root)
        return true;
    int left = height(root->getLeft());
    int right = height(root->getRight());
    int difference = right - left;
    bool balanced = (difference <= 1 && difference >= -1);
    return balanced && isBalanced(root->getLeft()) && isBalanced(root->getRight());
}

bool BinaryTree::isEmpty() const
{
    return m_root == nullptr;
}

int BinaryTree::height() const
{
    return height(m_root);
}

int BinaryTree::height(Node* root) const
{
    if (!root)
        return 0;
    else
    {
        int leftHeight = height(root->getLeft());
        int rightHeight = height(root->getRight());
        return std::max(leftHeight, rightHeight) + 1;
    }
}

int BinaryTree::nodeCount() const
{
    int result = 0;
    if (!m_root)
        return result;
    std::list<Node*> listNode;
    listNode.push_back(m_root);
    TreeToList(listNode);
    result = listNode.size();
    return result;
}

BinaryTree::Node* BinaryTree::root() const
{
    return m_root;
}

BinaryTree::Node* BinaryTree::add(const int key)
{
    if (m_root) {
        return _addNode(m_root, key);
    }
    else {
        return m_root = new Node(key);
    }
}

BinaryTree::Node* BinaryTree::_addNode(Node* root, int key)
{
    if (!root) {
        root = new Node(key);
    }
    else if (rand() % 2) {
        root->setLeft(_addNode(root->getLeft(), key));
    }
    else {
        root->setRight(_addNode(root->getRight(), key));
    }

    return root;
}

BinaryTree::Node* BinaryTree::find(const int key) const
{
    return find(m_root, key);
}

BinaryTree::Node* BinaryTree::find(Node* root, const int key) const
{
    if (!root)
        return nullptr;

    if (root->getKey() == key)
        return root;
    else
    {
        Node* node = find(root->getLeft(), key);
        if (!node)
            node = find(root->getRight(), key);
        return node;
    }
}

int BinaryTree::min() const
{
    if (!m_root)
        return INT_MIN;
    std::vector<int> vec = TreeToVector();
    return vec[0];
}

int BinaryTree::max() const
{
    if (!m_root)
        return INT_MAX;
    std::vector<int> vec = TreeToVector();
    return vec.back();
}

std::vector<int> BinaryTree::TreeToVector()const
{
    std::list<Node*> nodeList;
    std::vector<int> vec;
    if (!m_root)
        return vec;
    nodeList.push_back(m_root);
    TreeToList(nodeList);
    while (!nodeList.empty())
    {
        vec.push_back(nodeList.front()->getKey());
        nodeList.pop_front();
    }
    std::sort(begin(vec),end(vec));
    return vec;
}

void BinaryTree::printHorizontal(Node *root, int marginLeft, int levelSpacing) const {

    if (root == nullptr)
        return;


    printHorizontal(root->getRight(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->getKey() << std::endl;
    printHorizontal(root->getLeft(), marginLeft + levelSpacing, levelSpacing);
}

void BinaryTree::printHorizontal() const
{
    printHorizontal(m_root, 4, 4);
}

void BinaryTree::print() const
{
    print(m_root, 0, 8, 0);
}

void BinaryTree::print(Node *root, int leftBorderPos, int rightBorderPos, int yPos) const
{
    if (root == nullptr)
        return;


    int xPos = (leftBorderPos + rightBorderPos) / 2;
    moveCursor(xPos, yPos) ;
    std::cout << root->getKey();

    print(root->getLeft(), leftBorderPos, xPos, yPos + 15);
    print(root->getRight(), xPos, rightBorderPos, yPos + 15);
}

void BinaryTree::moveCursor(int xPos,int yPos  ) const
{
    COORD coord;
    coord.X = xPos;
    coord.Y = yPos;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void BinaryTree::printLeafs() const
{
    std::vector<Node*> vectorLeafs = leafsVector();
    for (Node* leafs : vectorLeafs)
    {
        std::cout << leafs->getKey() << " ";
    }
}

std::vector<BinaryTree::Node*> BinaryTree::leafsVector() const
{
    std::list<Node*> nodeList;
    std::vector<Node*> leafs;
    nodeList.push_back(m_root);
    TreeToList(nodeList);
    while (!nodeList.empty())
    {
        if (!nodeList.front()->getLeft() && !nodeList.front()->getRight())
        {
            leafs.push_back(nodeList.front());
        }
        nodeList.pop_front();
    }
    return leafs;
}




BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
    if (m_root == other.m_root)
        return *this;
    clear();
    m_root = other._copy(other.m_root);
    return* this;
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

