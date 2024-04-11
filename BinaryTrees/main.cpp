#include "binarytree.h"
#include <windows.h>
#include <iostream>
#include "BinaryTreeTester.h"
#include <cstdlib>
#include <ctime>
int main()
{
   /* BinaryTree tr;
    for(int i = 1; i < 10; ++i)
    {
        tr.add(i);
    }
    tr.printHorizontal();
    std::cout<<"\n"<<"-------------------------"<<"\n";
    tr.print();
    std::cout<<"\n"<<"-------------------------"<<"\n";


    tr.remove(1);
    tr.printHorizontal();*/


    srand(time(0));
    for (int i = 0; i < 10; ++i)
    {
        BinaryTreeTester tester(false, true);
        tester.setClearCheckEnabled(false);
        tester.setDestructorCheckEnabled(false);
        tester.test(200);
    }
    return 0;

}
