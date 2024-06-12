#include <iostream>
#include "HuffmanTree.h"

int main()
{
    
    HuffmanTree ht;


    ht.build("../../../text.txt");
    ht.printHorizontal();
    std::string str = "../../../text.txt";

    std::string encodeText = "encode.txt";
    std::cout << "compression ratio = " << ht.encode(str, encodeText) << std::endl;
    std::string decodeText = "decode.txt";
    ht.decode(encodeText, decodeText);

    return 0;
}