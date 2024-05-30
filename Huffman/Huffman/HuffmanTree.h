#pragma once
#include <vector>
#include"../../../TSU_Prog/OOP/OOP_LAB_3_(Ñlass of boolean vector)/OOP_LAB_3_(Ñlass of boolean vector)/BoolVector.h"
class HuffmanTree
{
public:
	class Node;
public:
	HuffmanTree() = default;
	~HuffmanTree() { clear(m_root); }

	void clear(Node* root);
	void build(const std::string& text);
	void createHuffmanTree();
	
	
	void printHorizontal() const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;

	static bool comparisonAlphafit( const BoolVector& vec1,  const BoolVector& vec2);
private:
	Node* m_root = nullptr;
	std::vector<int> m_frequencyTable;

public:
	struct NodeComparator
	{
		bool operator()(const Node* lhs, const Node* rhs) const;
	};

};


class HuffmanTree::Node
{
public:
	Node(const BoolVector& symbols, const int frequency, Node* left = nullptr, Node* right = nullptr);
	~Node() = default;
	int frequency()const;
	BoolVector symbols() const;
	Node* left()const;
	Node* right()const;
	void left(Node* left);
	void right(Node* right);
	

private:
	Node* m_left = nullptr;
	Node* m_right = nullptr;
	int m_frequency = 1;
	BoolVector m_symbols;
};
