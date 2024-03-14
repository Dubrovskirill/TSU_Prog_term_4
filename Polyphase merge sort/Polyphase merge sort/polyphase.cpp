#include<stdio.h>
#include<string>
#include<iostream>
#include <chrono>
#include <fstream>
#include<vector>
#include<iterator>

struct FileStruct
{
	int count = 6;
	std::string orig;
	std::string* fileName = nullptr;
	std::fstream fileStream;
	int* ip = nullptr;
	int* ms = nullptr;
	int L = 0;
	int countINT_MAX = 0;

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
	for (int i = file.count - 2; i >= 0; --i)
	{
		std::swap(file.fileName[i], file.fileName[i + 1]);
		std::swap(file.ms[i], file.ms[i + 1]);
		std::swap(fileVec[i], fileVec[i + 1]);
	}
}

void Rename(FileStruct& file)
{
	for (int i = 0; i < file.L-1; i++)
		for(int j=0;j<file.count-1;j++)
			std::swap(file.fileName[j], file.fileName[j + 1]);
	for (int k = 0; k < file.L-1; k++)
	{
		if (rename(file.fileName[file.count - 1].c_str(), "temp.txt"))
			std::cout << "error!";
		for (int i = file.count - 2; i >= 0; --i)
			if (rename(file.fileName[i].c_str(), file.fileName[i + 1].c_str()))
				std::cout << "error!";
		if (rename("temp.txt", file.fileName[0].c_str()))
			std::cout << "error!";
	}	
}

void ipmsForming(FileStruct& file)
{
	int ip0 = file.ip[0];
	for (int k = 0; k < file.count - 1; ++k)
	{
		file.ms[k] = file.ip[k + 1] - file.ip[k] + ip0;
		file.ip[k] = file.ip[k + 1] + ip0;
	}
	file.L++;
}

void PrintMS(FileStruct& file)
{
	for (int i = 0; i < file.count; i++)
		std::cout << file.ip[i] << " ";
	std::cout << "      ";

	for (int i = 0; i < file.count; i++)
		std::cout << file.ms[i] << " ";
	std::cout << std::endl;

}

void Splitting(FileStruct& file)
{
	for (int i = 0; i < file.count - 1; ++i)
	{
		file.ms[i] = file.ip[i] = 1;
	}
	file.ms[file.count - 1] = file.ip[file.count - 1] = 0;
	file.L++;

	std::vector<std::fstream> fileVec;
	for (int i = 0; i < file.count - 1; i++)
		fileVec.push_back(std::fstream(file.fileName[i], std::ios::out));
	
	int i = 0;
	int number = INT_MIN;
	int prev = INT_MIN;
	
	while(!file.fileStream.eof())
	{
		while (file.fileStream >> number && prev <= number)
		{
			if (number != INT_MAX)
			{
				fileVec[i] << number << " ";
				prev = number;
			}
			else file.countINT_MAX++;
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
			if (number != INT_MAX)
			{
				fileVec[i] << number << " ";
				prev = number;
			}
			else file.countINT_MAX++;
		}
	}

	for (int i = 0; i < file.count - 1; i++)
		fileVec[i].close();
}

int findMinIndex(const std::vector<int>& vec) {
	auto minIt = std::min_element(vec.begin(), vec.end());
	return std::distance(vec.begin(), minIt);
}

void Recording(FileStruct& file, std::vector<int> &vecMerg, std::vector<std::fstream>& fileVec, int number)
{
	for (int i = 0; i < file.count - 2; ++i)
	{
		int number = INT_MAX;
		if (file.ms[i] == 0)
		{
			fileVec[i] >> number;
			vecMerg.push_back(number);

		}
		else
		{
			file.ms[i]--;
			vecMerg.push_back(INT_MAX);
		}
	}
	vecMerg.push_back(number);
}

void Merging(FileStruct& file)
{
	std::vector<std::fstream> fileVec;
	for (int i = 0; i < file.count - 1; i++)
		fileVec.push_back(std::fstream(file.fileName[i], std::ios::in));
	fileVec.push_back(std::fstream(file.fileName[file.count-1], std::ios::out));
	int curL = file.L;
	while (curL != 0)
	{
		while (fileVec[file.count - 2])
		{
			bool mergeFictive = true;
			int i = 0;
			for (int i = 0; i < file.count - 1 && mergeFictive; ++i)
			{
				if (file.ms[i] == 0)
					mergeFictive = false;
			}
			if (mergeFictive)
			{
				for (int i = 0; i < file.count - 1; ++i)
					file.ms[i]--;
				file.ms[file.count - 1]++;
			}

			std::vector<int> vecMerg;
			int number =INT_MAX;
			if (file.ms[file.count - 2] == 0)
			{
				fileVec[file.count - 2] >> number;
				if (!fileVec[file.count - 2])
					break;
			}
			else file.ms[file.count - 2]--;
			Recording(file, vecMerg, fileVec, number);

			int minIndex = findMinIndex(vecMerg);
			while (vecMerg[minIndex] != INT_MAX)
			{
				fileVec[file.count - 1] << vecMerg[minIndex] << " ";
				fileVec[minIndex] >> number;
				vecMerg[minIndex] = number;
				minIndex = findMinIndex(vecMerg);
			}
			if (curL!=1)
				fileVec[file.count - 1] << INT_MAX << " ";
			else for(int i=0;i<file.countINT_MAX;i++)
				fileVec[file.count - 1] << INT_MAX << " ";
			
		}
		curL--;
		if (curL != 0)
		{
			fileVec[file.count - 1].close();
			fileVec[file.count - 1] = std::fstream(file.fileName[file.count - 1], std::ios::in);
			
			fileVec[file.count - 2].close();
			fileVec[file.count - 2] = std::fstream(file.fileName[file.count - 2], std::ios::out);
			ShiftFiles(file, fileVec);
		}
	}
	for (int i = 0; i < file.count; i++)
		fileVec[i].close();
}

std::string PolyphaseSort(std::string f, int count = 3)
{
	FileStruct file;
	file.count = count;
	file.orig = f;
	file.fileStream = std::fstream(file.orig, std::ios::in);
	if (file.fileStream.is_open() && count >= 3)
	{
		file.fileName = CreateFiles(file.count);
		file.ip = new int[file.count];
		file.ms = new int[file.count];
		Splitting(file);
		Merging(file);
		Rename(file);
		FreeMemory(file.fileName);
		file.fileStream.close();
		return "file_" + std::to_string(file.count-1) + ".txt";
	}
	file.fileStream.close();
	return file.orig;
}

bool isFileSorted(const std::string& filename) 
{
	std::ifstream inputFile(filename); 

	if (!inputFile) 
		return false;
	int prev;
	if (inputFile >> prev) 
	{ 
		int cur;
		while (inputFile >> cur) 
		{ 
			if (cur < prev)
			{
				inputFile.close();
				return false;
			}
			prev = cur; 
		}
	}
	inputFile.close(); 
	return true;
}

int countNumbersInFile(const std::string& filename) {
	std::ifstream file(filename);
	int count = 0;
	int number;

	while (file >> number) 
		count++;

	file.close();
	return count;
}

int main()
{
	
	int count = 100;
	std::string f = "../../../arr_size_1000000_in_range_100000.txt";
	std::string s = PolyphaseSort(f, count);
	if(s==f)
		std::cout << "File opening error";
	else if (isFileSorted(s))
		std::cout << "Sorted";
	else
		std::cout << "Not Sorted";
	std::cout << std::endl;
	
	return 0;
}