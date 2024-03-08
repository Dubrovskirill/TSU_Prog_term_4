#include<stdio.h>
#include<string>
#include<iostream>
#include <chrono>
#include <fstream>
#include<vector>
#include<iterator>

struct FileStruct
{
	int filesCount = 6;
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

void ShiftFiles(FileStruct& file, std::vector<std::fstream>& fileVec)
{	
	for (int i = file.filesCount - 2; i >= 0; --i)
	{
		std::swap(file.fileName[i], file.fileName[i + 1]);
		std::swap(file.ms[i], file.ms[i + 1]);
		std::swap(fileVec[i], fileVec[i + 1]);
	}
}

void Rename(FileStruct& file)
{
	for (int i = 0; i < file.L-1; i++)
		for(int j=0;j<file.filesCount-1;j++)
			std::swap(file.fileName[j], file.fileName[j + 1]);
	for (int k = 0; k < file.L-1; k++)
	{
		if (rename(file.fileName[file.filesCount - 1].c_str(), "temp.txt"))
			std::cout << "error!";
		for (int i = file.filesCount - 2; i >= 0; --i)
			if (rename(file.fileName[i].c_str(), file.fileName[i + 1].c_str()))
				std::cout << "error!";
		if (rename("temp.txt", file.fileName[0].c_str()))
			std::cout << "error!";
	}
	
}

void ipmsForming(FileStruct& file)
{
	int ip0 = file.ip[0];
	for (int k = 0; k < file.filesCount - 1; ++k)
	{
		file.ms[k] = file.ip[k + 1] - file.ip[k] + ip0;
		file.ip[k] = file.ip[k + 1] + ip0;
	}
	file.L++;
}

void Splitting(FileStruct& file)
{
	for (int i = 0; i < file.filesCount - 1; ++i)
	{
		file.ms[i] = file.ip[i] = 1;
	}
	file.ms[file.filesCount - 1] = file.ip[file.filesCount - 1] = 0;
	file.L++;

	file.fileStream = std::fstream(file.orig, std::ios::in);
	std::vector<std::fstream> fileVec;
	for (int i = 0; i < file.filesCount - 1; i++)
		fileVec.push_back(std::fstream(file.fileName[i], std::ios::out));
	

	int i = 0;
	int number = INT_MIN;
	int prev = INT_MIN;
	
	
	while(!file.fileStream.eof())
	{
		while (file.fileStream >> number && prev <= number)
		{
			fileVec[i] << number << " ";
			prev = number;
		}
		fileVec[i] << INT_MAX << " ";
		--file.ms[i];
		
		if (file.ms[i] < file.ms[i + 1])
			i++;
		else if (file.ms[i] == 0)
		{
			ipmsForming(file);
			i = 0;
		}
		else i = 0;
		if (file.fileStream)
		{
			fileVec[i] << number << " ";
			prev = number;
		}
	}

	for (int i = 0; i < file.filesCount - 1; i++)
		fileVec[i].close();
	file.fileStream.close();

}

int findMinIndex(const std::vector<int>& vec) {
	auto minIt = std::min_element(vec.begin(), vec.end());
	return std::distance(vec.begin(), minIt);
}

void Merging(FileStruct& file)
{
	std::vector<std::fstream> fileVec;
	for (int i = 0; i < file.filesCount - 1; i++)
		fileVec.push_back(std::fstream(file.fileName[i], std::ios::in));
	fileVec.push_back(std::fstream(file.fileName[file.filesCount-1], std::ios::out));
	int curL = file.L;
	while (curL != 0)
	{
		
			bool check = true;
			int i = 0;
			for (int i = 0; i < file.filesCount - 1 && check; ++i)
				if (file.ms[i] == 0)
					check = false;
			if (check)
			{
				for (int i = 0; i < file.filesCount - 1; ++i)
					file.ms[i]--;
				file.ms[file.filesCount - 1]++;
			}
			//возможно стоит переписать
			std::vector<int> vec;
			for (int i = 0; i < file.filesCount - 1; ++i)
			{
				int number= INT_MAX;
				if (file.ms[i] == 0)
				{
					fileVec[i] >> number;
					vec.push_back(number);
					
				}
				else
				{
					file.ms[i]--;
					vec.push_back(INT_MAX);
				}
			}
			
			int minIndex = findMinIndex(vec);
			fileVec[file.filesCount - 1] << vec[minIndex]<<" ";
			int number;
			while (vec[minIndex] != INT_MAX)
			{
				fileVec[minIndex] >> number;
				vec[minIndex]=number;

				minIndex = findMinIndex(vec);
				fileVec[file.filesCount - 1] << vec[minIndex] << " ";
			}

		
		curL--;
		if (curL != 0)
		{
			fileVec[file.filesCount - 1].close();
			fileVec[file.filesCount - 1] = std::fstream(file.fileName[file.filesCount - 1], std::ios::in);
			
			fileVec[file.filesCount - 2].close();
			fileVec[file.filesCount - 2] = std::fstream(file.fileName[file.filesCount - 2], std::ios::out);
			ShiftFiles(file, fileVec);
		}
		

	}

	for (int i = 0; i < file.filesCount; i++)
		fileVec[i].close();
	
}

void PolyphaseSort(FileStruct& file)
{

	
	file.fileName = CreateFiles(file.filesCount);
	file.ip = new int[file.filesCount];
	file.ms = new int[file.filesCount];
	Splitting(file);

	Merging(file);
	Rename(file);
	FreeMemory(file.fileName);
}

int main()
{
	FileStruct file;
	file.filesCount = 6;
	file.orig = "../../../test.txt";
	//file.orig = "../../../arr_size_10000_in_range_10.txt";
	PolyphaseSort(file);
	
	
	
	return 0;
}