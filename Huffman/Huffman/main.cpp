#include <iostream>
#include "HuffmanTree.h"

int main()
{
   

    HuffmanTree huffmanTree;

   
    huffmanTree.build("../../../text.txt");
    huffmanTree.printHorizontal();
    HuffmanTree huffmanTree2;
    std::string str = "../../../text.txt";

    std::string encodeText = "encode.txt";
    std::cout << "compression ratio = " << huffmanTree.encode(str, encodeText) << std::endl;
    std::string decodeText = "decode.txt";
    huffmanTree.decode(encodeText, decodeText);

 

    return 0;
}