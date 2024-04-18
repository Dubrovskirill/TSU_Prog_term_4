#include "SearchTree.h"
#include "../../BinaryTrees/binarytree.h"



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
    if (isEmpty())
        return INT_MIN;

    Node* current = root();
    while (current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    return current->getKey();
}

int SearchTree::max() const {
    if (isEmpty())
        return INT_MIN;

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
    Node* removableNode = BinaryTree::find(key);
    if (!removableNode)
        return false;

    if (isLeafOrRoot(removableNode)) {
        handleLeafOrRootRemoval(removableNode);
    } else if (hasOneChild(removableNode)) {
        handleOneChildRemoval(removableNode);
    } else {
        handleTwoChildrenRemoval(removableNode);
    }

    return true;
}

bool SearchTree::isLeafOrRoot(Node* node) const {
    return !node->getLeft() && !node->getRight();
}

bool SearchTree::hasOneChild(Node* node) const {
    return (node->getLeft() && !node->getRight()) || (!node->getLeft() && node->getRight());
}

void SearchTree::handleLeafOrRootRemoval(Node* node) {
    if (node == m_root) {
        delete m_root;
        m_root = nullptr;
    } else {
        Node* parentNode = parent(node);
        if (node->getKey() < parentNode->getKey()) {
            parentNode->setLeft(nullptr);
        } else {
            parentNode->setRight(nullptr);
        }
        delete node;
    }
}

void SearchTree::handleOneChildRemoval(Node* node) {
    Node* replacementNode = node->getLeft() ? node->getLeft() : node->getRight();
    Node* parentNode = parent(node);
    if (parentNode) {
        if (node->getKey() < parentNode->getKey())
            parentNode->setLeft(replacementNode);
        else
            parentNode->setRight(replacementNode);
    } else {
        m_root = replacementNode;
    }
    delete node;
}

void SearchTree::handleTwoChildrenRemoval(Node* node) {
    Node* parentNode = parent(node);
    Node* replacementNode = findReplacementNode(node);
    Node* parentReplacementNode = parent(replacementNode);

    if (!replacementNode->getLeft()) {
        replacementNode->setRight(node->getRight());
        if (parentNode) {
            if (parentNode->getLeft() == node)
                parentNode->setLeft(replacementNode);
            else
                parentNode->setRight(replacementNode);
        }
        if (parentReplacementNode != node) {
            replacementNode->setLeft(node->getLeft());
            parentReplacementNode->setRight(nullptr);
        }
    } else {
        replacementNode->setRight(node->getRight());
        if (parentNode) {
            if (parentNode->getLeft() == node)
                parentNode->setLeft(replacementNode);
            else
                parentNode->setRight(replacementNode);
        }
        if (parentReplacementNode != node) {
            parentReplacementNode->setRight(replacementNode->getLeft());
            replacementNode->setLeft(node->getLeft());
        }
    }
    if (node == m_root)
        m_root = replacementNode;
    delete node;
}

BinaryTree::Node* SearchTree::findReplacementNode(Node* root) const {
    Node* tmpRoot = root->getLeft();
    while (tmpRoot) {
        if (tmpRoot && !tmpRoot->getRight())
            return tmpRoot;
        tmpRoot = tmpRoot->getRight();
    }
    return nullptr;
}
