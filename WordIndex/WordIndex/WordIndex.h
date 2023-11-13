#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#define HASH_TABLE_SIZE 19
#define HASH_WORDS_FILE "hashWords.txt"

class Hash {
private:
	std::string* hashTable;
	int hashTableSize;
	int hashWordsCount;
	int maxWordLength;
	void ExtensionHashTable();
	int FindHashTableIndex(std::string word);
	int HashFunction(std::string word);
	void InitHashTable();
public:
	Hash();
	~Hash();
	void AddHashTable(std::string word);
	void DeleteHash(std::string word);
	bool IsInHashTable(std::string word);
	void PrintHashTable();
};

class WordBST {
public:
	struct Line {
		int index;
		Line* nextIndex;
	};
	struct Node {
		Node* leftChild;
		std::string word;
		Line* lineHead;
		Node* rightChild;
	};
private:
	Node* rootNode;
	Node* currentNode;
	Node* parentNode;
	void AddIndex(int index);
	Line* CreateLine(int index);
	void DeleteIndexAll();
	Node* CreateNode(std::string word);
	bool IsInWordBST(std::string word);
	void DeleteNoChildNode();
	void DeleteOneChildNode();
	void DeleteTwoChildNode();
	void DeleteWordBST(Node* root);
	void PrintWordIndex(Node* iter, std::ostream& os = std::cout);
public:
	WordBST();
	~WordBST();
	void AddWordBST(std::string word, int index);
	void DeleteWordBSTNode(std::string word);
	void DeleteWordBSTAll();
	bool InputFile(const char* file, Hash& hashTable);
	bool Output(std::ostream& os = std::cout);
};

std::vector<std::string> Tokenize(std::string line);