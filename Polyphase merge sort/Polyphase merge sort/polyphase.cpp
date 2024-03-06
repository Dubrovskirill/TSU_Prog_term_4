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
	file.L++;

	file.fileStream = std::fstream(file.orig, std::ios::in);
	std::vector<std::fstream> fileVec;
	for (int i = 0; i < file.filesNumber - 1; i++)
	{
		fileVec.push_back(std::fstream(file.fileName[i], std::ios::out));
	}

	int i = 0;
	int number = INT_MIN;
	int prev = INT_MIN;
	file.fileStream >> number;
	
	while(!file.fileStream.eof())
	{
		prev = INT_MIN;
		while (prev <= number && !file.fileStream.eof())
		{
			fileVec[i] << number << " ";
			prev = number;
			file.fileStream >> number;
		}
		
		--file.ms[i];
		
		if (file.ms[i] < file.ms[i + 1])
			i++;
		else if (file.ms[i] == 0)
		{
			ipmsForming(file);
			i = 0;
		}
		else i = 0;

		if (file.fileStream.eof())
		{
			fileVec[i] << number << " ";
			--file.ms[i];
		}
		
	}

	for (int i = 0; i < file.filesNumber - 1; i++)
		fileVec[i].close();
	file.fileStream.close();

}

void PolyphaseSort(FileStruct& file)
{

	
	file.fileName = CreateFiles(file.filesNumber);
	file.ip = new int[file.filesNumber];
	file.ms = new int[file.filesNumber];
	Splitting(file);

	
	FreeMemory(file.fileName);
}

int main()
{
	FileStruct file;
	file.filesNumber = 6;
	file.orig = "../../../test.txt";
	//file.orig = "../../../arr_size_10000_in_range_10.txt";
	
	PolyphaseSort(file);
	return 0;
}