#include <iostream>
#include "HuffmanTree.h"

int main()
{


    HuffmanTree ht;


    ht.build("../../../text.txt");
    ht.printTable();
    ht.printHorizontal();


    return 0;
}