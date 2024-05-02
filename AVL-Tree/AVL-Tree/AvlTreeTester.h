#pragma once
#include"../../BinarySearchTree/SearchTreeTester.h"

class AvlTreeTester : public SearchTreeTester
{
public:
    AvlTreeTester(const bool useConsoleOutput, const bool enableAllTests = true);
	~AvlTreeTester() override = default;
protected:
    BinaryTree* allocateTree()override;
    void check_addAndCount(const BinaryTree* tree, const int size)override;
    void check_remove(BinaryTree* tree, const int key, const bool result, const int size)override;
    void check_clear(const BinaryTree* tree, const int size)override;
    void check_assign(const BinaryTree* first, const BinaryTree* second)override;
    void assign() override;
};

