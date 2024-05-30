#include <iostream>
#include "HuffmanTree.h"

int main()
{
    HuffmanTree huffmanTree;

   
    huffmanTree.build("../../../text.txt");
    huffmanTree.printHorizontal();
    HuffmanTree huffmanTree2;

  
    return 0;
}