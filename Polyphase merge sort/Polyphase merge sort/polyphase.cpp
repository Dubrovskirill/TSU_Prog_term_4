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
	if (rename(file.fileName[file.filesCount - 1].c_str(), "temp.txt"))
		std::cout << "erorr!";
	for (int i = file.filesCount - 2; i >= 0; --i)
	{
		if (rename(file.fileName[i].c_str(), file.fileName[i + 1].c_str()))
			std::cout << "erorr!";

		std::swap(file.fileName[i], file.fileName[i + 1]);
		std::swap(file.ms[i], file.ms[i + 1]);
		std::swap(file.ip[i], file.ip[i + 1]);

	}
	if (rename("temp.txt", file.fileName[0].c_str()))
		std::cout << "erorr!";
	std::swap(file.fileName[0], file.fileName[file.filesCount-1]);
	std::swap(file.ms[0], file.ms[file.filesCount - 1]);
	std::swap(file.ip[0], file.ip[file.filesCount - 1]);
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
		/*for (int i = 0; i < file.filesCount; i++)
		{
			std::cout << file.ms[i] << " ";
		}
		std::cout << "   ";
		for (int i = 0; i < file.filesCount; i++)
		{
			std::cout << file.ip[i] << " ";
		}
		std::cout << std::endl;*/

		
		while (file.fileStream >> number && prev <= number)
		{
			fileVec[i] << number << " ";
			prev = number;
		}
		fileVec[i] << INT_MIN << " ";
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
			//fileVec[i] << INT_MIN << " ";
			prev = number;
		}

		/*if (file.fileStream.eof())
		{
			fileVec[i] << number << " ";
			--file.ms[i];
		}*/

		
	}

	for (int i = 0; i < file.filesCount - 1; i++)
		fileVec[i].close();
	file.fileStream.close();

}

//void Merging(FileStruct& file)
//{
//	std::vector<std::fstream> fileVec;
//	for (int i = 0; i < file.filesCount - 1; i++)
//		fileVec.push_back(std::fstream(file.fileName[i], std::ios::in));
//	fileVec.push_back(std::fstream(file.fileName[file.filesCount - 1], std::ios::out));
//	while (file.L != 0)
//	{
//		//std::cout << file.L << " ";
//		while (!fileVec[file.filesCount - 2].eof())
//		{
//			for (int i = 0; i < file.filesCount; i++)
//			{
//				std::cout << file.ms[i] << " ";
//			}
//			std::cout << "   ";
//			for (int i = 0; i < file.filesCount; i++)
//			{
//				std::cout << file.ip[i] << " ";
//			}
//			std::cout << std::endl;
//			bool check = true;
//			for (int i = 0; i < file.filesCount - 1; ++i)
//				if (file.ms[i] <= 0)
//					check = false;
//			if (check)
//			{
//				for (int i = 0; i < file.filesCount - 1; --file.ms[i], i++);
//				file.ms[file.filesCount]++;
//			}
//
//			for (int i = 0; i < file.filesCount; i++)
//			{
//				std::cout << file.ms[i] << " ";
//			}
//			std::cout << "   ";
//			for (int i = 0; i < file.filesCount; i++)
//			{
//				std::cout << file.ip[i] << " ";
//			}
//			std::cout << std::endl;
//			for (int i = 0; i < file.filesCount - 1; ++i)
//			{
//
//				if (file.ms[i] == 0)
//				{
//					int number = 0;
//					int prev = INT_MIN;
//					fileVec[i] >> number;
//					while (prev <= number && !fileVec[i].eof())
//					{
//						fileVec[i] << number << " ";
//						fileVec[i] >> number;
//						prev = number;
//						
//					}
//				}
//				if (file.ms[i] > 0)
//					file.ms[i]--;
//			}
//		}
//		file.L--;
//		fileVec[file.filesCount-1].close();
//		fileVec.push_back(std::fstream(file.fileName[file.filesCount - 1], std::ios::in));
//		fileVec[file.filesCount-2].close();
//		fileVec.push_back(std::fstream(file.fileName[file.filesCount - 2], std::ios::out));
//		ShiftFiles(file, fileVec);
//
//
//	}
//	
//	for (int i = 0; i < file.filesCount; i++)
//		fileVec[i].close();
//
//	
//}

void PolyphaseSort(FileStruct& file)
{

	
	file.fileName = CreateFiles(file.filesCount);
	file.ip = new int[file.filesCount];
	file.ms = new int[file.filesCount];
	Splitting(file);
	//Merging(file);
	
	//FreeMemory(file.fileName);
}

int main()
{
	FileStruct file;
	file.filesCount = 6;
	file.orig = "../../../test.txt";
	//file.orig = "../../../arr_size_10000_in_range_10.txt";
	PolyphaseSort(file);
	std::cout << "\n";
	std::vector<std::fstream> fileVec;
	for (int i = 0; i < file.filesCount; i++)
	{
		int num;
		fileVec.push_back(std::fstream(file.fileName[i], std::ios::in));
		while (fileVec[i] >> num)
		{
			std::cout <<num<<" ";
		}
		std::cout << "\n";
	}
	FreeMemory(file.fileName);
	
	return 0;
}