#include "binarytree.h"



int main()
{

    BinaryTree tr;
    for(int i = 1; i < 18; ++i)
        tr.add(i);
    tr.print();
    tr.printLeafs();
    return 0;
}
