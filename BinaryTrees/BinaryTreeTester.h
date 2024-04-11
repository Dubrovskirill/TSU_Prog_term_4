#pragma once
#include<vector>
#include"BinaryTree.h"

class BinaryTreeTester
{
public:
    BinaryTreeTester(const bool useConsoleOutput, const bool enableAllTests = true);
    virtual ~BinaryTreeTester() = default;

    void test(const int size);

    bool addAndCountCheckEnabled() const;
    bool destructorCheckEnabled() const;
    bool removeCheckEnabled() const;
    bool clearCheckEnabled() const;
    bool assignCheckEnabled() const;
    bool heightCheckEnabled() const;

    void setAddAndCountCheckEnabled(const bool enabled);
    void setDestructorCheckEnabled(const bool enabled);
    void setRemoveCheckEnabled(const bool enabled);
    void setClearCheckEnabled(const bool enabled);
    void setAssignCheckEnabled(const bool enabled);
    void setHeightCheckEnabled(const bool enabled);

protected:
    using TreeNodes = std::vector<BinaryTree::Node*>;

protected:
    int invalidKey() const;

    virtual BinaryTree* allocateTree();
    virtual void check_addAndCount(const BinaryTree* tree, const int size);
    virtual void check_remove(BinaryTree* tree, const int key,
        const bool result, const int size);
    virtual void check_clear(const BinaryTree* tree, const int size);
    virtual void check_assign(const BinaryTree* first,
        const BinaryTree* second);
    virtual void check_height(const BinaryTree& tree, const int size);

private:
    void deallocateTree(BinaryTree* tree);
    void addAndCount();
    void destructor();
    void remove();
    void clear(); //ToDo: реализовать
    void assign();
    void height();
    void height_trivialCases();
    void height_longOnlyLeftSubtree();
    void height_longOnlyRightSubtree();
    void height_longOnlyLeftAndRightSubtrees();
    void height_longRandomZigzagSubtrees();
    TreeNodes treeNodes(const BinaryTree* tree);

private:
    int m_maxSize;
    bool m_useConsoleOutput;
    bool m_addAndCountCheckEnabled;
    bool m_destructorCheckEnabled;
    bool m_removeCheckEnabled;
    bool m_clearCheckEnabled;
    bool m_assignCheckEnabled;
    bool m_heightCheckEnabled;
};

