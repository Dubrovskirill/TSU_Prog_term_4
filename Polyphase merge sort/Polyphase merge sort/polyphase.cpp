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

void ipmsForming(FileStruct& file)
{
	int ip0 = file.ip[0];
	for (int k = 0; k < file.filesNumber - 1; ++k)
	{
		file.ms[k] = file.ip[k + 1] - file.ip[k] + ip0;
		file.ip[k] = file.ip[k + 1] + ip0;
	}
	file.L++;

}

void Splitting(FileStruct& file)
{
	for (int i = 0; i < file.filesNumber - 1; ++i)
	{
		file.ms[i] = file.ip[i] = 1;
	}
	file.ms[file.filesNumber - 1] = file.ip[file.filesNumber - 1] = 0;

	ipmsForming(file);

	int number;
	int prev = INT_MIN;
	while (file.fileStream >> number)
	{
		if (prev > number) std::cout << std::endl;
		std::cout << number << " ";
		prev = number;
		while (file.fileStream >> number && prev < number)
		{
			std::cout << number << " ";
			prev = number;
		}
		std::cout << std::endl;
		std::cout << number << " ";
		prev = number;
	}

}

void PolyphaseSort(FileStruct& file)
{

	file.orig = "../../../arr_size_10000_in_range_1000.txt";
	file.fileName = CreateFiles(file.filesNumber);
	file.ip = new int[file.filesNumber];
	file.ms = new int[file.filesNumber];
	file.fileStream = std::fstream(file.orig, std::ios::in);
	Splitting(file);

	file.fileStream.close();
	FreeMemory(file.fileName);
}

int main()
{

	return 0;
}