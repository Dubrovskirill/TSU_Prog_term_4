#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../../BinarySearchTree/SearchTree.h"
#include "../../BinarySearchTree/SearchTreeTester.h"

#include "../../BinaryTrees/binarytree.h"
#include "../../BinaryTrees/BinaryTreeTester.h"
int main()
{
    SearchTreeTester tester(false);
    tester.test(1000);
    return 0;


    BinaryTree tr;
    for (int i = 0; i < 1500; ++i)
    {
        tr.add(i);
        

    }

    tr.print_3(tr.root());
    /*for (int i = 1500; i >= 0; --i)
    {
        tr.remove(i);
 

    }*/
    tr.clear();
    tr.print_3(tr.root());

    return 0;
}
