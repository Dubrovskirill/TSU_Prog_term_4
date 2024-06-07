#include <fstream>
#include <list>
#include <string>
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
