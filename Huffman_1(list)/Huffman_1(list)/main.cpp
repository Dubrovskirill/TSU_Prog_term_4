#include <iostream>
#include <fstream>
#include <string>
#include "HuffmanTree.h"
bool isEqual(std::string originalFilename, std::string decodedFilename){

	std::ifstream orginalFile(originalFilename, std::ios::binary);
	if (!orginalFile.is_open())
	{
		std::cerr << "ERROR open file for read: " << originalFilename << std::endl;
		return false;
	}

	std::ifstream decodeFile(decodedFilename, std::ios::binary);
	if (!decodeFile.is_open())
	{
		std::cerr << "ERROR open file for write: " << decodedFilename << std::endl;
		return false;
	}

    std::istreambuf_iterator<char> begin1(orginalFile), end1;
    std::istreambuf_iterator<char> begin2(decodeFile), end2;

    if (std::equal(begin1, end1, begin2, end2)) {
        return true;
    }
    else {
        return false;
    }
}
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
    if (isEqual) {
        std::cout << "DecodeFile is correct";
    }
    else {
        std::cout << "DecodeFile isn't correct";
    }
    return 0;
}