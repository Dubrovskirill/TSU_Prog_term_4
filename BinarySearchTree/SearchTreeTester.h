#pragma once

#include "../../BinaryTrees/BinaryTreeTester.h"


class SearchTreeTester : public BinaryTreeTester
{
public:
	SearchTreeTester(const bool useConsoleOutput, const bool enableAllTests = true);
    ~SearchTreeTester() override = default;
protected:
    BinaryTree* allocateTree()override;
    void check_addAndCount(const BinaryTree* tree, const int size)override;
    void check_remove(BinaryTree* tree, const int key, const bool result, const int size)override;
    void check_clear(const BinaryTree* tree, const int size)override;
    void check_assign(const BinaryTree* first, const BinaryTree* second)override;
    void assign() override;
private:
    bool isSearchTree(const BinaryTree* tree);
    void treeKeysLnr(BinaryTree::Node* root, std::vector<int>& keys);
};

    
