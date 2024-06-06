#include "HuffmanTree.h"
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <queue>
#include<map>

void HuffmanTree::clear(Node* root) {
	if (!root) {
		return;
	}
	if (root->left()) {
		clear(root->left());
		root->left(nullptr);
	}
	if (root->right()) {
		clear(root->right());
		root->right(nullptr);
	}

	delete root;
}









void HuffmanTree::build(const std::string& fileName) {
	clear(m_root);

	std::ifstream inputFile(fileName, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open file: " << fileName << std::endl;
		return;
	}

	std::list<Node*> nodeList;
	m_frequencyTable.assign(256, 0);

	unsigned char ch;
	inputFile >> std::noskipws;
	inputFile >> ch;
	while (!inputFile.eof())
	{
		m_frequencyTable[ch]++;
		inputFile >> ch;
	}
	inputFile.close();

	createHuffmanTree();
}

void HuffmanTree::createHuffmanTree()
{
	std::priority_queue<Node*, std::vector<Node*>, NodeComparator> pq;

	for (int i = 0; i < 256; i++)
	{
		if (m_frequencyTable[i] > 0)
		{
			BoolVector symbols(256, 0);
			symbols[i] = true;
			Node* node = new Node(symbols, m_frequencyTable[i]);
			pq.push(node);

		}
	}


	while (pq.size() > 1)
	{
		Node* left = pq.top();
		printSim(left->symbols());
		pq.pop();
		Node* right = pq.top();
		printSim(right->symbols());
		pq.pop();

		BoolVector combinedSymbols = left->symbols() | right->symbols();
		int combinedFrequency = left->frequency() + right->frequency();
		Node* parent = new Node(combinedSymbols, combinedFrequency, left, right);
		pq.push(parent);
	}


	m_root = pq.top();
	pq.pop();

}

void HuffmanTree::printSim(const BoolVector& vec1)
{
	int order1 = 0;
	for (int i = 0; i < vec1.CellCount(); ++i)
	{
		uint8_t mask = 1 << (vec1.m_cellSize - 1);
		for (int j = 0; j < vec1.m_cellSize; ++j)
		{
			if (vec1.Data()[i] & mask)
				break;
			mask >>= 1;
			++order1;
		}
	}
	std::cout << order1<<" ";
}
bool HuffmanTree::NodeComparator::operator()(const Node* lhs, const Node* rhs) const
{
	if (lhs->frequency() == rhs->frequency()) {
		return comparisonAlphafit(lhs->symbols(), rhs->symbols());
	}
	return lhs->frequency() > rhs->frequency();
}

bool HuffmanTree::comparisonAlphafit(const BoolVector& vec1, const BoolVector& vec2) {
	int order1 = 0;
	for (int i = 0; i < vec1.CellCount(); ++i)
	{
		uint8_t mask = 1 << (vec1.m_cellSize - 1);
		for (int j = 0; j < vec1.m_cellSize; ++j)
		{
			if (vec1.Data()[i] & mask)
				break;
			mask >>= 1;
			++order1;
		}
	}


	int order2 = 0;
	for (int i = 0; i < vec2.CellCount(); ++i)
	{
		uint8_t mask = 1 << (vec2.m_cellSize - 1);
		for (int j = 0; j < vec2.m_cellSize; ++j)
		{
			if (vec2.Data()[i] & mask)
				break;
			mask >>= 1;
			++order2;
		}
	}

	return order1 > order2;
}





void HuffmanTree::printHorizontal() const
{
	printHorizontal(m_root, 0, 4);
}

void HuffmanTree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
	if (root == nullptr) {
		return;
	}

	printHorizontal(root->right(), marginLeft + levelSpacing, levelSpacing);
	for (int i = 0; i < 256; ++i)
	{
		if (root->symbols()[i] == true)
			std::cout << std::string(marginLeft, ' ') << static_cast<char>(i) << std::endl;
	}
	printHorizontal(root->left(), marginLeft + levelSpacing, levelSpacing);
}

void prependDataToFile(const std::string& originFilename, const int data)
{
	std::ifstream inputFile(originFilename, std::ios::binary);
	if (!inputFile.is_open()) {
		std::cerr << "Failed to open file for reading:: " << originFilename << std::endl;
		return;
	}

	std::string tempFileName = "temp_" + originFilename;
	std::ofstream outputFile(tempFileName, std::ios::binary);
	if (!outputFile.is_open()) {
		std::cerr << "Failed to create a temporary file:" << tempFileName << std::endl;
		return;
	}

	outputFile << data;
	outputFile << inputFile.rdbuf();

	outputFile.close();
	inputFile.close();

	if (std::remove(originFilename.c_str())) {
		std::cerr << "Error delete: " << originFilename << std::endl;
		return;
	}

	if (std::rename(tempFileName.c_str(), originFilename.c_str())) {
		std::cerr << "Error rename: " << tempFileName << std::endl;
		return;
	}
}

float HuffmanTree::encode(const std::string& inputFilename, const std::string& outputFilename)
{
	if (!m_root)
		build(inputFilename);

	std::ifstream inputFile(inputFilename, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open file for reading: " << inputFilename << std::endl;
		return -1;
	}

	std::ofstream outputFile(outputFilename, std::ios::binary);
	if (!outputFile.is_open())
	{
		std::cerr << "Failed to open file for writing: " << outputFilename << std::endl;
		return -1;
	}

	unsigned char ch;
	BoolVector code(256, 0);
	int pos = 0;
	int countCharInput = 0, countCharOutput = 0;
	inputFile >> std::noskipws;
	inputFile >> ch;
	++countCharInput;
	while (!inputFile.eof())
	{
		if (!encodeSymbol(ch, code, pos))
		{
			std::cerr << "Encoding failed: the function is called by another tree" << std::endl;
			return 0;
		}

		const unsigned char* symbPtr = code.Data();
		int i = 0;
		for (; i < (pos / 8); ++i)
		{
			outputFile << symbPtr[i];
			++countCharOutput;
		}
		if (pos / 8)
		{
			code = code << i * 8;
			pos = pos % 8;
		}

		inputFile >> ch;
		++countCharInput;
		if (inputFile.eof() && (pos % 8))
		{
			outputFile << symbPtr[0];
			++countCharOutput;
		}
	}
	--countCharInput;
	inputFile.close();
	outputFile.close();

	if (pos == 0)
	{
		prependDataToFile(outputFilename, 0);
	}
	else
	{
		prependDataToFile(outputFilename, 8 - pos);
	}

	return ((static_cast<float>(countCharOutput) / static_cast<float>(countCharInput)) * 100);
}



bool HuffmanTree::encodeSymbol(const unsigned char symbol, BoolVector& code, int& pos)
{

	if (!m_root)
		return false;

	Node* currentNode = m_root;
	while (currentNode->left() || currentNode->right())
	{
		if (currentNode->symbols()[static_cast<int>(symbol)])
		{
			code[pos++] = true;
			currentNode = currentNode->right();
		}
		else
		{
			code[pos++] = false;
			currentNode = currentNode->left();
		}
	}

	return true;
}


bool HuffmanTree::decode(const std::string& encodedFilename, const std::string& decodedFilename)
{
	if (!m_root)
		return false;

	std::ifstream inputFile(encodedFilename, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open file for reading: " << encodedFilename << std::endl;
		return false;
	}

	std::ofstream outputFile(decodedFilename, std::ios::binary);
	if (!outputFile.is_open())
	{
		std::cerr << "Failed to open file for writing: " << decodedFilename << std::endl;
		return false;
	}

	unsigned char ch;
	int insignificantBits;
	inputFile >> std::noskipws;
	inputFile >> insignificantBits;

	Node* currentNode = m_root;

	while (!inputFile.eof())
	{
		inputFile >> ch;
		for (int i = 0; i < 8; i++)
		{
			bool bit = (ch & (1 << (7 - i))) != 0;
			if (bit)
			{
				currentNode = currentNode->right();
			}
			else
			{
				currentNode = currentNode->left();
			}

			if (!currentNode->left() && !currentNode->right())
			{
				for (int j = 0; j < currentNode->symbols().Lenght(); j++)
				{
					if (currentNode->symbols()[j])
					{
						outputFile << static_cast<char>(j);
						break;
					}
				}
				currentNode = m_root;
			}
		}
	}

	
	for (int i = 0; i < 8 - insignificantBits; i++)
	{
		bool bit = (ch & (1 << (7 - i))) != 0;
		if (bit)
		{
			currentNode = currentNode->right();
		}
		else
		{
			currentNode = currentNode->left();
		}

		if (!currentNode->left() && !currentNode->right())
		{
			for (int j = 0; j < currentNode->symbols().Lenght(); j++)
			{
				if (currentNode->symbols()[j])
				{
					outputFile << static_cast<char>(j);
					break;
				}
			}
			currentNode = m_root;
		}
	}

	inputFile.close();
	outputFile.close();

	return true;
}

int HuffmanTree::encodedFileSize(const std::string& filename)
{
	std::ifstream inputFile(filename, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open file for reading: " << filename << std::endl;
		return -1;
	}

	inputFile.seekg(0, std::ios::end);
	int fileSize = inputFile.tellg();
	inputFile.close();
	return fileSize;
}




HuffmanTree::Node::Node(const BoolVector& symbols, const int frequency, Node* left, Node* right)
	: m_symbols(symbols)
	, m_frequency(frequency)
	, m_left(left)
	, m_right(right)
{}

int HuffmanTree::Node::frequency() const
{
	return m_frequency;
}

BoolVector HuffmanTree::Node::symbols() const
{
	return m_symbols;
}

HuffmanTree::Node* HuffmanTree::Node::left()const
{
	return m_left;
}

HuffmanTree::Node* HuffmanTree::Node::right()const
{
	return m_right;
}

void HuffmanTree::Node::left(Node* left)
{
	m_left = left;
}

void HuffmanTree::Node::right(Node* right)
{
	m_right = right;
}

