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

private:

	
	float encode(const std::string& inputFilename, const std::string& outputFilename);
	bool decode(const std::string& encodedFilename, const std::string& decodedFilename);

	void printHorizontal() const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;

	void printSim(const BoolVector& vec1);

	static bool comparisonAlphafit( const BoolVector& vec1,  const BoolVector& vec2);
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
	bool encodeSymbol(const unsigned char symbol, BoolVector& code, int& pos);
	void createHuffmanTree();
	bool _decode(std::ofstream& ostream, DecodeData& data);
	int encodedFileSize(const std::string& filename);
	


	

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
	bool operator<(const Node& other) const {
		return frequency() > other.frequency();
	}
	

private:
	Node* m_left = nullptr;
	Node* m_right = nullptr;
	int m_frequency = 1;
	BoolVector m_symbols;
};
