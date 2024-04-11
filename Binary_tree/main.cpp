#include "binarytree.h"

#include <iostream>

int main()
{


    BinaryTree tr;
    for(int i = 1; i < 10; ++i)
    {
        tr.add(i);
    }
    tr.printHorizontal();
    std::cout<<"\n"<<"-------------------------"<<"\n";
    tr.remove(4);
    tr.printHorizontal();


}
