#include <iostream>
#include "../../BinaryTrees/binarytree.h"
#include "../../BinaryTrees/BinaryTreeTester.h"
#include <cstdlib>
#include <ctime>
int main()
{

   BinaryTree tr;
    for (int i = 1; i < 30; ++i)
    {
        tr.add(i);
    }

    tr.print_2(tr.root());
    std::cout << "\n" << "-------------------------" << "\n";
    tr.printHorizontal();
    tr.remove(1);
    //tr.printTreeWin(tr.root());
    
    return 0;

}
