#include "SearchTree.h"
#include "../BinaryTrees/BinaryTreeTester.h"
#include <cassert>


BinaryTree::Node* SearchTree::_addNode(Node* root, const int key)  {
    if(!root) {
        root = new Node(key);
    } else if(key < root->getKey()) {
        root->setLeft(_addNode(root->getLeft(), key));
    } else if(key > root->getKey()){
        root->setRight(_addNode(root->getRight(), key));
    }
    return root;
}

SearchTree SearchTree::copy() const
{
    return copy(m_root);
}

SearchTree SearchTree::copy(Node* root) const
{
    BinaryTree tempTree = BinaryTree::copy(root);
    SearchTree newSearchTree;
    newSearchTree.m_root = _copy(tempTree.root());
    return newSearchTree;
}

BinaryTree::Node* SearchTree::find(const int key) const {
    return find(root(), key);
}

BinaryTree::Node* SearchTree::find(Node* root, const int key) const {
    if (root == nullptr || root->getKey() == key) {
        return root;
    }
    if (key < root->getKey()) {
        return find(root->getLeft(), key);
    }
    return find(root->getRight(), key);
}

int SearchTree::min() const {
    assert(isEmpty());

    Node* current = root();
    while (current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    return current->getKey();
}

int SearchTree::max() const { 
    assert(isEmpty());

    Node* current = root();
    while (current->getRight() != nullptr) {
        current = current->getRight();
    }
    return current->getKey();
}

int SearchTree::level(const int key) const {
    return level(root(), key, 0);
}

int SearchTree::level(Node* root, const int key, int currentLevel) const {
    if (root == nullptr)
        return -1;


    if (root->getKey() == key)
        return currentLevel;

    int leftLevel = level(root->getLeft(), key, currentLevel + 1);

    if (leftLevel != -1)
        return leftLevel;

    return level(root->getRight(), key, currentLevel + 1);
}


std::vector<int> SearchTree::keysVector() const {
    std::vector<int> keys;
    keysVector(m_root, keys);
    return keys;
}

std::vector<int> SearchTree::keysVector(Node* root, std::vector<int>& keys)const {
    if (!root)
        return keys;
    keysVector(root->getLeft(), keys);
    keys.push_back(root->getKey());
    keysVector(root->getRight(), keys);
}


bool SearchTree::remove(const int key) {
    Node* node = find(key);
    if (!node)
        return false;
    if (!node->getLeft() && !node->getRight())
        return removeLeafNode(node);
    else if (!node->getLeft() || !node->getRight())
        return removeNodeWithOneChild(node);
    else
        return removeNodeWithTwoChildren(node);

    return false;
}


bool SearchTree::removeLeafNode(Node* node) {
    Node* parentNode = parent(node);
    if (node == m_root)
    {
        delete m_root;
        m_root = nullptr;
        return true;
    }
    if (node->getKey() < parentNode->getKey())
        parentNode->setLeft(nullptr);
    else
        parentNode->setRight(nullptr);
    delete node;
    return true;
}

bool SearchTree::removeNodeWithOneChild(Node* node) {
    Node* parentNode = parent(node);
    Node* child = (node->getLeft()) ? node->getLeft() : node->getRight();

    if (node->getKey() < parentNode->getKey()) {
        if(parentNode != node) {
            parentNode->setLeft(child);
        } else {
            m_root = child;
        }
    } else {
        if(parentNode != node) {
            parentNode->setRight(child);
        } else {
            m_root = child;
        }
    }
    delete node;
    return true;
}

bool SearchTree::removeNodeWithTwoChildren(Node* node) {
    if (!node) {
        return true;
    }

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
    } else {
        Node* parentNode = parent(node);
        if (parentNode)
        {
            if (parentNode->getLeft() == node)
                parentNode->setLeft(replacementNode);
            else
                parentNode->setRight(replacementNode);
        }
    }

    return true;
}

BinaryTree::Node* SearchTree::findReplacement(Node* root) const {
    Node* tmpRoot = root->getLeft();
    while (tmpRoot && tmpRoot->getRight())
        tmpRoot = tmpRoot->getRight();
    return tmpRoot;
}




