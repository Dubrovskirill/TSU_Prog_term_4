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

void AvlTree::balance(Node*& root, Node* nodeSide) {
    if (nodeSide == root) {
        return;
    }
    switch (bFactor(root)) {
    case 0:
        isFixed = true;
        break;

    case 2:
        if (bFactor(nodeSide) == 1) {

            Node* p = parent(this->root());
            if (p == root)
                p = nullptr;
            root = turnDoubleLR(root, p);
        }
        else {
            Node* p = parent(this->root());
            if (p == root)
                p = nullptr;
            root = turnRight(root, p);
        }
        isFixed = true;
        break;

    case -2:

        if (bFactor(nodeSide) == -1) {
            Node* p = parent(this->root());
                if (p == root)
                    p = nullptr;
                root = turnDoubleRL(root, p);
        }
        else {
            Node* p = parent(this->root());
                if (p == root)
                    p = nullptr;
            root = turnLeft(root, p);
        }
        isFixed = true;
        break;
    }

}