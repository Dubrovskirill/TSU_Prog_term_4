#include <iostream>
#include "../../BinaryTrees/binarytree.h"
#include "../../BinaryTrees/BinaryTreeTester.h"
#include "../../BinarySearchTree/SearchTree.h"
#include "../../BinarySearchTree/SearchTreeTester.h"

#include <cstdlib>
#include <ctime>
int main()
{
    SearchTree tr;
    int arr[12] = { 10,6,16,2,8,14,20,1,4,12,18,25 };
    for (int i = 0; i < 12; ++i)
    {
        tr.add(arr[i]);
        tr.print_3(tr.root());
        std::cout << std::endl;
    }
    tr.remove(6);
    tr.print_3(tr.root());
    tr.remove(4);
    tr.print_3(tr.root());
   
    return 0;
    srand(time(0));
    SearchTreeTester tester(false);
    tester.test(1000);

    return 0;
}
