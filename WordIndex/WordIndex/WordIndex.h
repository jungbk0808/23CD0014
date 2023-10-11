#pragma once
#include <iostream>
#include <string>
#include <fstream>

struct Line {
	int index;
	Line* next;
};

struct Node { //클래스로 만들기 ??
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
	//해쉬 테이블 생성
	std::string* CreateHashTable();
	//해쉬 테이블에 새로운 key 추가
	void AddHashTable(std::string* hashTable, std::string word);
	//해쉬 테이블의 특정 값 삭제
	void DeleteHash(std::string* hashTable, std::string word);
	//해쉬 테이블 삭제
	void DeleteHashTable(std::string* hashTable);
	//해쉬 탐색
	bool IsInHashTable(std::string* hashTable, std::string word);
	//해쉬 함수
	int HashFunction(std::string word);
	//해쉬 테이블 출력(표준 출력만 지원)
	void PrintHashTable(std::string* hashTable);
};

//이진 탐색 트리를 생성
Node* CreateWordBST(std::string word, int index);
//이진 탐색 트리의 노드를 추가
void AddWordBST(Node** root, std::string word, int index);
//이진 탐색 트리를 삭제
void DeleteWordBSTAll(Node** root);
//이진 탐색 트리의 노드를 삭제
void DeleteWordBSTNode(Node** root, std::string word);
//인덱스 추가
void AddIndex(Line* head);
//인덱스 모두 삭제
void DeleteIndexAll(Line* head);
//파일로부터 텍스트 입력
bool InputFile(const char* file);
//출력
bool Output(std::ostream os);