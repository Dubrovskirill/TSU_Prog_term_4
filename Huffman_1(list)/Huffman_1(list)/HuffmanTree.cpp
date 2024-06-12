#include <fstream>
#include <list>
#include <string>
#include <queue>
#include "HuffmanTree.h"

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

void HuffmanTree::printTable()
{
	for (int i = 0; i < m_frequencyTable.size(); i++)
	{
		std::cout<<i<<": " << m_frequencyTable[i] << "\n";
	}
}

void HuffmanTree::createHuffmanTree()
{
	std::list<Node*> listNode;

	for (int i = 0; i < 256; i++)
	{
		if (m_frequencyTable[i] > 0)
		{
			BoolVector symbols(256, 0);
			symbols[i] = true;
			Node* node = new Node(symbols, m_frequencyTable[i]);
			auto it = listNode.rbegin();
			while (it != listNode.rend()
				&& (*it)->frequency() > node->frequency()) {
				++it;
			}
			listNode.insert(it.base(), node);
			
		}
	}
	
	while (listNode.size() > 1) {
		Node* left = listNode.front();
		listNode.pop_front();
		Node* right = listNode.front();
		listNode.pop_front();

		BoolVector combinedSymbols = left->symbols() | right->symbols();
		Node* parent = new Node(combinedSymbols, left->frequency() + right->frequency());
		parent->left(left);
		parent->right(right);
		auto it = listNode.rbegin();
		while (it != listNode.rend()
			&& (*it)->frequency() > parent->frequency()) {
			++it;
		}
		listNode.insert(it.base(), parent);
		
	}
	m_root = listNode.front();
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

float HuffmanTree::encode(const std::string& inputFilename, const std::string& outputFilename) {

	if (!m_root) {
		build(inputFilename); 
	}

	
	std::ifstream inputFile(inputFilename, std::ios::binary);
	if (!inputFile.is_open()) {
		std::cerr << "ERROR open file for read: " << inputFilename << std::endl;
		return -1;
	}


	std::ofstream outputFile(outputFilename, std::ios::binary);
	if (!outputFile.is_open()) {
		std::cerr << "ERROR open file for write: " << outputFilename << std::endl;
		return -1;
	}

	unsigned char buffer = 0; 
	int bitPos = 0; 

	
	size_t inputBytes = 0, outputBytes = 0;

	char ch;
	while (inputFile.get(ch)) { 
		++inputBytes;

		BoolVector code(256, 0); 
		int codeLength = 0;

		if (!encodeSymbol(ch, code, codeLength)) { 
			std::cerr << "ERROR encoding" << std::endl;
			return 0;
		}

		for (int i = 0; i < codeLength; ++i) {
			if (code[i]) { 
				buffer |= (1 << (7 - bitPos)); 
			}
			++bitPos;

			if (bitPos == 8) { 
				outputFile.put(buffer); 
				++outputBytes;
				buffer = 0; 
				bitPos = 0; 
			}
		}
	}

	
	if (bitPos > 0) {
		outputFile.put(buffer);
		++outputBytes;
	}

	inputFile.close(); 
	outputFile.close();


	prependDataToFile(outputFilename, bitPos == 0 ? 0 : 8 - bitPos);

	
	return (static_cast<float>(outputBytes) / static_cast<float>(inputBytes)) * 100;

}

bool HuffmanTree::encodeSymbol(const unsigned char symbol, BoolVector& code, int& pos){
	Node* root = m_root;
	if (!m_root->left() && !m_root->right())
	{
		code[pos] = true;
		++pos;
		return true;
	}

	while (root->left() || root->right())
	{
		if (root->left()->symbols()[symbol] == true)
		{
			root = root->left();
			code[pos] = false;
			++pos;
		}
		else if (root->right()->symbols()[symbol] == true)
		{
			root = root->right();
			code[pos] = true;
			++pos;
		}
		else
		{
			return false;
		}
	}
	return true;
}



bool HuffmanTree::decode(const std::string& encodedFilename, std::string& decodedFilename)
{
	std::ifstream encodeFile(encodedFilename, std::ios::binary);
	if (!encodeFile.is_open())
	{
		std::cerr << "ERROR open file for read: " << encodedFilename << std::endl;
		return false;
	}
	std::ofstream decodeFile(decodedFilename, std::ios::binary);
	if (!decodeFile.is_open())
	{
		std::cerr << "ERROR open file for write: " << decodedFilename << std::endl;
		return false;
	}
	encodeFile >> std::noskipws;
	unsigned char insignificantBits;
	encodeFile >> insignificantBits;
	unsigned char ch;
	encodeFile >> ch;
	DecodeData data;
	data.m_path.addSymbol(ch, 0);
	data.m_insignificantBits = insignificantBits - '0';
	data.m_node = m_root;
	
	if (encodeFile.peek() == EOF)
	{
		data.m_flagEOF = true;
		while (data.m_pos != 8 - data.m_insignificantBits)
		{
			decodeSymbol(decodeFile, data);
		}
	}
	while (!encodeFile.eof())
	{
		bool isDecode = decodeSymbol(decodeFile, data);
		if ((isDecode && (data.m_pos == 8)) || !isDecode)
		{
			encodeFile >> ch;
			data.m_path.addSymbol(ch, 0);
			data.m_pos = 0;
			if (encodeFile.peek() == EOF)
			{
				data.m_flagEOF = true;
				for (;;)
				{
					if (!decodeSymbol(decodeFile, data))
					{
						encodeFile.close();
						decodeFile.close();
						std::cerr << "Can't decode!" << std::endl;
						return false;
					}
					if (data.m_pos == 8 - data.m_insignificantBits)
						break;
				}
			}
		}
	}
	encodeFile.close();
	decodeFile.close();
	return true;
}

bool HuffmanTree::decodeSymbol(std::ofstream& ostream, DecodeData& data)
{
	unsigned char ch;
	int insignificantBits = 0;
	if (data.m_flagEOF)
	{
		insignificantBits = data.m_insignificantBits;
	}
	if (!m_root->left() && !m_root->right())
	{
		for (int i = 0; i < 256; ++i)
		{
			if (m_root->symbols()[i] == true)
			{
				ch = static_cast<unsigned char>(i);
				break;
			}
		}
		for (; data.m_pos < 8 - insignificantBits; ++data.m_pos)
		{
			ostream << ch;
		}
		return true;
	}
	for (; data.m_pos < 8 - insignificantBits; ++data.m_pos)
	{
		if (data.m_path[data.m_pos] == false)
		{
			data.m_node = data.m_node->left();
			if (!data.m_node->left() && !data.m_node->right())
			{
				for (int j = 0; j < 256; j++)
				{
					if (data.m_node->symbols()[j] == true)
					{
						ch = static_cast<unsigned char>(j);
						break;
					}
				}
				ostream << ch;
				data.m_node = m_root;
				++data.m_pos;
				return true;
			}
		}
		else
		{
			data.m_node = data.m_node->right();
			if (!data.m_node->left() && !data.m_node->right())
			{
				for (int j = 0; j < 256; j++)
				{
					if (data.m_node->symbols()[j] == true)
					{
						ch = static_cast<unsigned char>(j);
						break;
					}
				}
				ostream << ch;
				data.m_node = m_root;
				++data.m_pos;
				return true;
			}
		}
	}
	return false;
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

bool HuffmanTree::Node::isLeaf() const {
	
   return left() == nullptr && right() == nullptr;
}


void HuffmanTree::exportTree(const std::string& filename)
{
	if (!m_root)
	{
		std::cerr << "Tree is empty. Can't export" << std::endl;
		return;
	}
	std::ofstream file(filename);
	for (int i = 0; i < m_frequencyTable.size(); ++i)
	{
		file << m_frequencyTable[i] << " ";
	}
	file.close();
}

void HuffmanTree::importTree(const std::string& filename)
{
	if (m_root)
	{
		clear(m_root);
	}
	std::ifstream file(filename);
	int frequency;
	file >> frequency;
	for (int i = 0; i < 256; ++i)
	{
		m_frequencyTable[i] = frequency;
		file >> frequency;
	}
	createHuffmanTree();
}


