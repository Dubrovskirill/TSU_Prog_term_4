#include<stdio.h>
#include<string>
#include<iostream>
#include <chrono>
#include <fstream>
#include<vector>
#include<iterator>

struct FileStruct
{
	int filesNumber = 6;
	std::string orig;
	std::string* fileName = nullptr;
	std::fstream fileStream;
	int* ip = nullptr;
	int* ms = nullptr;
	int L = 0;

};

std::string* CreateFiles(int filesNumber)
{
	std::string* fileName = new std::string[filesNumber];
	for (int i = 0; i < filesNumber; ++i)
	{
		std::string s = "file_" + std::to_string(i) + ".txt";
		fileName[i] = s;
		std::ofstream file(s);
		file.close();
	}
	return fileName;
}

void FreeMemory(std::string* fileName)
{
	delete[] fileName;
}

void ShiftFiles(std::string* fileName, int filesNumber)
{
	if (rename(fileName[filesNumber - 1].c_str(), "temp.txt"))
		std::cout << "erorr!";
	for (int i = filesNumber - 2; i >= 0; --i)
	{
		if (rename(fileName[i].c_str(), fileName[i + 1].c_str()))
			std::cout << "erorr!";
	}
	if (rename("temp.txt", fileName[0].c_str()))
		std::cout << "erorr!";
}

int main()
{

	return 0;
}