#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex> //���Խ� ��ġ�� tokenization ����


#define HASH_TABLE_SIZE 19
#define HASH_WORDS_FILE "hashWords.txt"

class Hash {
private:
	std::string* hashTable; //�ؽ� ���̺�
	int hashTableSize; //�ؽ� ���̺��� ũ��
	int hashWordsCount; //�ؽ� ���̺��� �ܾ� ����
	int maxWordLength; //�ؽ� ���̺��� ���� �� �ܾ��� ����
	//�ؽ� ���̺� �ʱ�ȭ
	void InitHashTable();
	//�ؽ� ���̺� Ȯ��
	void ExtensionHashTable();
public:
	//�ؽ� ���̺� ����
	Hash();
	//�ؽ� ���̺� ���ο� key �߰�
	void AddHashTable(std::string word);
	//�ؽ� ���̺��� Ư�� �� ����
	void DeleteHash(std::string word);
	//�ؽ� ���̺� ����
	void DeleteHashTable();
	//�ؽ� Ž��
	bool IsInHashTable(std::string word);
	//�ؽ� �Լ�
	int HashFunction(std::string word);
	//�ؽ� ���̺� ���(ǥ�� ��¸� ����)
	void PrintHashTable();
};

struct Line {
	int index;
	Line* next;
};

struct Node { //Ŭ������ ����� ??
	Node* left;
	std::string word;
	Line* Head;
	Node* right;
};

//���� Ž�� Ʈ���� ����
Node* CreateWordBST(std::string word, int index);
//���� Ž�� Ʈ���� ��带 �߰�
void AddWordBST(Node** root, std::string word, int index);
//���� Ž�� Ʈ���� ����
void DeleteWordBSTAll(Node** root);
//���� Ž�� Ʈ���� ��带 ����
void DeleteWordBSTNode(Node** root, std::string word);
//�ε��� �߰�
void AddIndex(Line* head);
//�ε��� ��� ����
void DeleteIndexAll(Line* head);
//���Ϸκ��� �ؽ�Ʈ �Է�
bool InputFile(const char* file);
//�Է¹��� ���� tokenize
std::vector<std::string> Tokenize(std::string line);
//���
bool Output(std::ostream& os = std::cout);