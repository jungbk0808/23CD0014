#pragma once
#include <iostream>
#include <string>
//#include <fstream>

struct Line {
	int num;
	Line* next;
};

struct Node { //Ŭ������ ����� ??
	Node* left;
	std::string word;
	Line* Head;
	Node* right;
};

//���� Ž�� Ʈ���� ����
Node* CreateWordBST();
//���� Ž�� Ʈ���� ��带 �߰�
void AddWordBST(Node** root);
//���� Ž�� Ʈ���� ����
void DeleteWordBSTAll(Node** root);
//���� Ž�� Ʈ���� ��带 ����
void DeleteWordBSTNode(Node** root);
//�ε��� �߰�
void AddIndex(Line* head);
//�ε��� ��� ����
void DeleteIndexAll(Line* head);
//�ؽ� ���̺� ����
std::string* CreateHashTable();
//�ؽ� ���̺� ���ο� key �߰�
void AddHashTable(string* hashTable);
//�ؽ� ���̺��� Ư�� �� ����
void DeleteHash(string* hashTable, string deleteValue);
//�ؽ� ���̺� ����
void DeleteHashTable(string* hashTable);
//�ؽ� �Լ�
int HashFunction(string Value);
//���Ϸκ��� �ؽ�Ʈ �Է�
bool InputFile(const char* fileName);
//���
bool Output(std::ostream os);