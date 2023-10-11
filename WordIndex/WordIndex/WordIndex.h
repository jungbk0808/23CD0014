#pragma once
#include <iostream>
#include <string>
#include <fstream>

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

#define HASH_SIZE 23

class Hash {
private:
	int maxWordLength;
public:
	//�ؽ� ���̺� ����
	std::string* CreateHashTable();
	//�ؽ� ���̺� ���ο� key �߰�
	void AddHashTable(std::string* hashTable, std::string word);
	//�ؽ� ���̺��� Ư�� �� ����
	void DeleteHash(std::string* hashTable, std::string word);
	//�ؽ� ���̺� ����
	void DeleteHashTable(std::string* hashTable);
	//�ؽ� Ž��
	bool IsInHashTable(std::string* hashTable, std::string word);
	//�ؽ� �Լ�
	int HashFunction(std::string word);
	//�ؽ� ���̺� ���(ǥ�� ��¸� ����)
	void PrintHashTable(std::string* hashTable);
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
//���
bool Output(std::ostream os);