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
	bool decode(const std::string& encodedFilename,  std::string& decodedFilename);

	void printTable();
	void printHorizontal() const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;

	void exportTree(const std::string& filename);
	void importTree(const std::string& filename);
	
private:
	Node* m_root = nullptr;
	std::vector<int> m_frequencyTable;
	
	struct DecodeData
	{
		int m_insignificantBits;
		bool m_flagEOF;
		Node* m_node;
		int m_pos;
		BoolVector m_path;

		DecodeData(int insignificantBits = 0, bool flagEOF = false, Node* node = nullptr, int pos = 0)
			: m_insignificantBits(insignificantBits)
			, m_flagEOF(flagEOF)
			, m_node(node)
			, m_pos(pos)
		{

		}
	};

private:
	void createHuffmanTree();
	bool encodeSymbol(const unsigned char symbol, BoolVector& code, int& pos);
	bool decodeSymbol(std::ofstream& ostream, DecodeData& data);
	

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
	bool operator!=(const Node* other) const { return symbols() != other->symbols();  }
	bool isLeaf() const;

private:
	
	Node* m_left = nullptr;
	Node* m_right = nullptr;
	int m_frequency = 1;
	BoolVector m_symbols;
};

