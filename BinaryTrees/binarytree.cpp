#include "binarytree.h"

#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <windows.h>
#include <queue>
#include <cmath>
#undef max
#undef min


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
    nodeList(listForClearNode);
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
void BinaryTree::nodeList(std::list<Node*>& nodeList) const
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
    nodeList(listNode);
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
    std::vector<int> vec = keysVector();
    return vec[0];
}

int BinaryTree::max() const
{
    if (!m_root)
        return INT_MAX;
    std::vector<int> vec = keysVector();
    return vec.back();
}

std::vector<int> BinaryTree::keysVector()const //keysVector
{
    std::list<Node*> nodeL;
    std::vector<int> vec;
    if (!m_root)
        return vec;
    nodeL.push_back(m_root);
    nodeList(nodeL); //NodeList
    while (!nodeL.empty())
    {
        vec.push_back(nodeL.front()->getKey());
        nodeL.pop_front();
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
    print(m_root, 0, 30, 0);
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
    std::list<Node*> nodeL;
    std::vector<Node*> leafs;
    nodeL.push_back(m_root);
    nodeList(nodeL);
    while (!nodeL.empty())
    {
        if (!nodeL.front()->getLeft() && !nodeL.front()->getRight())
        {
            leafs.push_back(nodeL.front());
        }
        nodeL.pop_front();
    }
    return leafs;
}

int BinaryTree::level(const int key) const
{
    return level(m_root, key, 1);
}

int BinaryTree::level(Node* root, const int key, int currentLevel) const
{
    if (!root)
        return -1;
    if (root->getKey() == key)
        return currentLevel;
    int downLevel = level(root->getLeft(), key, currentLevel + 1);
    if (downLevel == -1)
        return level(root->getRight(), key, currentLevel + 1);

    return{} ;
}

BinaryTree::Node* BinaryTree::parent(const Node* child) const
{
    if (m_root == child)
        return m_root;
    Node* current = nullptr;
    std::list<Node*> nodeL;
    nodeL.push_back(m_root);
    nodeList(nodeL);
    while (!nodeL.empty())
    {
        current = nodeL.front();
        if (current->getLeft() == child)
        {
            return current;
        }
        else if (current->getRight() == child)
        {
            return current;
        }
        nodeL.pop_front();
    }
    return nullptr;
}

bool BinaryTree::remove(const int key)
{

    Node* removableNode = find(key);
    if (!removableNode)
        return false;

    if (removableNode == m_root)
        return removeRootNode(removableNode);
    if (!removableNode->getLeft() && !removableNode->getRight())
        return removeLeafNode(removableNode);
    if (removableNode->getLeft() && removableNode->getRight())
        return removeNodeWithTwoChildren(removableNode);

    return removeNodeWithOneChild(removableNode);
}
bool BinaryTree::removeRootNode(Node* node)
{
    std::list<Node*> listTree;
    listTree.push_back(node);
    nodeList(listTree);
    Node* replacementNode = nullptr;
    Node* parentNode = nullptr;
    if (!node->getLeft() && !node->getRight())
    {
        delete node;
        m_root = nullptr;
        return true;
    }
    replacementNode = listTree.back();
    parentNode = parent(replacementNode);
    if (parentNode->getLeft() == replacementNode)
        parentNode->setLeft(nullptr);
    else if(parentNode->getRight() == replacementNode)
        parentNode->setRight(nullptr);
    replacementNode->setLeft(node->m_left);
    replacementNode->setRight(node->m_right);
    delete node;
    m_root = replacementNode;
    return true;
}



bool BinaryTree::removeLeafNode(Node* node)
{
    Node* parentNode = parent(node);
    if (parentNode->getLeft() == node)
        parentNode->setLeft(nullptr);
    else if (parentNode->getRight() == node)
        parentNode->setRight(nullptr);
    delete node;
    return true;
}

bool BinaryTree::removeNodeWithTwoChildren(Node* node)
{
    Node* parentNode = parent(node);
    std::vector<Node*> vecLeafs = _leafs(node);
    Node* replacementNode = vecLeafs.back();
    Node* parentReplacementNode = parent(replacementNode);
    if (replacementNode != node->getLeft())
        replacementNode->setLeft(node->getLeft());
    if (replacementNode != node->getRight())
        replacementNode->setRight(node->getRight());
    if (parentReplacementNode->getLeft() == replacementNode)
        parentReplacementNode->setLeft(nullptr);
    else
        parentReplacementNode->setRight(nullptr);
    if (parentNode->getLeft() == node)
        parentNode->setLeft(replacementNode);
    else if (parentNode->getRight() == node)
        parentNode->setRight(replacementNode);
    delete node;
    return true;
}

bool BinaryTree::removeNodeWithOneChild(Node* node)
{
    Node* parentNode = parent(node);
    Node* replacementNode = nullptr;
    if (node->getLeft())
        replacementNode = node->getLeft();
    else if(node->getRight())
        replacementNode = node->getRight();
    if (parentNode->getLeft() == node)
        parentNode->setLeft(replacementNode);
    else if (parentNode->getRight() == node)
        parentNode->setRight(replacementNode);
    delete node;
    return true;
}

void BinaryTree::getLeafs(Node* node, std::vector<Node*>& leafs)
{
    if (!node)
        return;

    if (!node->getLeft() && !node->getRight())
        leafs.push_back(node);

    getLeafs(node->getLeft(), leafs);
    getLeafs(node->getRight(), leafs);
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



std::vector<BinaryTree::Node*> BinaryTree::_leafs(Node* root) const
{
    std::list<Node*> nodeL;
    std::vector<Node*> leafs;
    nodeL.push_back(root);
    nodeList(nodeL);
    while (!nodeL.empty())
    {
        if (!nodeL.front()->getLeft() && !nodeL.front()->getRight())
        {
            leafs.push_back(nodeL.front());
        }
        nodeL.pop_front();
    }
    return leafs;
}

int BinaryTree::size() const
{
    std::vector<int> vec = keysVector();
    return vec.size();
}

void BinaryTree::print(Node* root, int leftBorderPos, int rightBorderPos, int yPos) const
{
    if (root == nullptr)
        return;


    int xPos = (leftBorderPos + rightBorderPos) / 2;
    moveCursor(xPos, yPos);
    std::cout << root->getKey() << std::endl;

    print(root->getLeft(), leftBorderPos, xPos, yPos + 15);
    print(root->getRight(), xPos, rightBorderPos, yPos + 15);
}
//не работает
void BinaryTree::moveCursor(int xPos, int yPos) const
{
    COORD coord;
    coord.X = xPos;
    coord.Y = yPos;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void BinaryTree::print_2( Node* root, int level, int xPos, int yPos, int xShift) const {
    if (root == nullptr) 
        return;
    

    xPos = xPos + xShift;

    moveCursor(xPos, yPos);
    std::cout << root->getKey();

    if (root->getLeft()) {
        print_2(root->getLeft(), level + 1, xPos - xShift, yPos + 2, xShift / 2);
    }

    if (root->getRight()) {
        print_2(root->getRight(), level + 1, xPos + xShift, yPos + 2, xShift / 2);
    }
}

void BinaryTree::print_2(Node* root) const {
    print_2(root, 1, 40, 1, 20);
    std::cout << std::endl;
}


void BinaryTree::printSpaces(int count) 
{
    for (int i = 0; i < count; ++i) 
        std::cout << " "; 
}

// Функция для вывода двоичного дерева
void BinaryTree::print_3(Node* root)
{
    int he = height(root);
    std::queue<Node*> q;
    q.push(root);

    int levelNodes = 1;
    int level = 0;
    int maxLevelWidth = pow(2, he) - 1;

        while (!q.empty() && level <= he) {
        int width = maxLevelWidth / pow(2, level);
            int padding = width / 2;
            printSpaces(padding);

            for (int i = 0; i < levelNodes; ++i) {
                Node* current = q.front();
                q.pop();
                if (current != nullptr) {
                    std::cout << current->getKey();
                    q.push(current->getLeft());
                    q.push(current->getRight());
                }
                else {
                    std::cout << " ";
                    q.push(nullptr);
                    q.push(nullptr);
                }
                printSpaces(width); // Увеличиваем отступ между узлами

            }
                std::cout << std::endl;

                levelNodes *= 2;
                ++level; 
        }
}       

