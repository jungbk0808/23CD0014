#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex> //정규식 일치로 tokenization 위함

#define HASH_TABLE_SIZE 19
#define HASH_WORDS_FILE "hashWords.txt"

class Hash {
private:
	std::string* hashTable;
	int hashTableSize;
	int hashWordsCount;
	int maxWordLength;
	void InitHashTable();
	void ExtensionHashTable();
public:
	Hash();
	~Hash();
	void AddHashTable(std::string word);
	void DeleteHash(std::string word);
	bool IsInHashTable(std::string word);
	int HashFunction(std::string word);
	void PrintHashTable();
};

class WordBST {
private:
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
	Node* rootNode;
	Node* currentNode;
	Node* parentNode;
	bool IsInWordBST(std::string word);
	void AddIndex(int index);
	void DeleteIndexAll();
	void DeleteNoChildNode();
	void DeleteOneChildNode();
	void DeleteTwoChildNode();
public:
	WordBST();
	void AddWordBST(std::string word, int index);
	void DeleteWordBSTNode(std::string word);
	void DeleteWordBSTAll();
	~WordBST();
};

bool InputFile(const char* file);
std::vector<std::string> Tokenize(std::string line);
bool Output(std::ostream& os = std::cout);