#include <iostream>
#include "HuffmanTree.h"

int main()
{
   

    HuffmanTree huffmanTree;

   
    huffmanTree.build("../../../text.txt");
    huffmanTree.printHorizontal();
    HuffmanTree huffmanTree2;
    std::string str = "../../../text.txt";

   

 

    return 0;
}