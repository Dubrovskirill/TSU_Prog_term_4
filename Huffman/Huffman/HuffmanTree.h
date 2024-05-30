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
	
	float encode(const std::string& inputFilename, const std::string& outputFilename);
	bool decode(const std::string& encodedFilename, const std::string& decodedFilename);
	int encodedFileSize(const std::string& filename);
	void printHorizontal() const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;

	static bool comparisonAlphafit( const BoolVector& vec1,  const BoolVector& vec2);

private:
	bool encodeSymbol(const char symbol, BoolVector& code, int& pos);
	void createHuffmanTree();
	
private:
	Node* m_root = nullptr;
	std::vector<int> m_frequencyTable;
	struct DecodeData
	{
		int m_insignificantBits;
		bool m_flagEOF;
		Node* m_currentNode;
		int m_position;
		BoolVector m_path;

		DecodeData(int insignificantBits = 0, bool flagEOF = false, Node* node = nullptr, int pos = 0)
			: m_insignificantBits(insignificantBits)
			, m_flagEOF(flagEOF)
			, m_currentNode(node)
			, m_position(pos)
		{
		}
	};

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
