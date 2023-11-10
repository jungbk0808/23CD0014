#include "WordIndex.h"

const std::string nullString = std::string("");

void Hash::InitHashTable() {
	hashWordsCount = 0;
	maxWordLength = 0;
	hashTable = new std::string[hashTableSize];
	for (int i = 0; i < hashTableSize; i++) {
		hashTable[i] = nullString; //빈 string으로 초기화
	}
}
Hash::Hash() {
	hashTableSize = HASH_TABLE_SIZE;
	InitHashTable();
	std::ifstream ifs(HASH_WORDS_FILE);
	if (ifs.is_open()) {
		std::string tmp;
		while (!ifs.eof()) {
			ifs >> tmp;
			AddHashTable(tmp);
			if (tmp.size() > maxWordLength) {
				maxWordLength = tmp.size();
			}
		}
	}
}
Hash::~Hash() {
	delete[] hashTable;
}
void Hash::ExtensionHashTable() {
	std::string* oldHashTable = hashTable;
	int oldHashTableSize = hashTableSize;
	hashTableSize *= 2;
	InitHashTable();
	for (int i = 0; i < oldHashTableSize; i++) {
		if (oldHashTable[i] != nullString) {
			AddHashTable(oldHashTable[i]);
		}
	}
	delete[] oldHashTable;
}
void Hash::AddHashTable(std::string word) {
	hashWordsCount++;
	if (hashWordsCount >= hashTableSize) {
		ExtensionHashTable();
		return;
	}
	int hashValue = HashFunction(word) % hashTableSize;
	while (hashTable[hashValue] != nullString) {
		hashValue = (hashValue + 1) % hashTableSize;
	}
	hashTable[hashValue] = word;
}
void Hash::DeleteHash(std::string word) {
	int index = FindHashTableIndex(word);
	int nextIndex = index + 1;
	if (index != -1) {
		if (hashTable[nextIndex] != nullString) {
			if (HashFunction(hashTable[nextIndex]) != nextIndex) {
				hashTable[index] = std::string("!");
			}
		}
		hashTable[index] = nullString;
	}
}
bool Hash::IsInHashTable(std::string word) {
	if (word.size() <= maxWordLength) {
		if (FindHashTableIndex(word) != -1) {
			return true;
		}
	}
	return false;
}
int Hash::FindHashTableIndex(std::string word) {
	int hashValue = HashFunction(word);
	int index = hashValue;
	do {
		if (hashTable[index] == word) {
			return index;
		}
		else if (hashTable[index] == nullString) {
			break;
		}
		index = (index + 1) % hashTableSize;
	} while (index != hashValue);
	return -1;
}
int Hash::HashFunction(std::string word) {
	int hashValue = 0;
	int wordSize = word.size();
	for (int i = 0; i < wordSize; i++) {
		hashValue += word[i];
	}
	return hashValue % hashTableSize;
}
void Hash::PrintHashTable() {
	for (int i = 0; i < hashTableSize; i++) {
		std::cout << i << '\t' << hashTable[i] << std::endl;
	}
}
bool WordBST::IsInWordBST(std::string word) {
	currentNode = rootNode;
	while (currentNode != NULL) {
		parentNode = currentNode;
		if (currentNode->word > word) {
			currentNode = parentNode->leftChild;
		}
		else if (currentNode->word < word) {
			currentNode = parentNode->rightChild;
		}
		else {
			return true;
		}
	}
	return false;
}
WordBST::Line* WordBST::CreateLine(int index) {
	Line* newIndex = new Line;
	newIndex->index = index;
	newIndex->nextIndex = NULL;
	return newIndex;
}
void WordBST::AddIndex(int index) {
	if (currentNode == NULL) return;
	if (currentNode->lineHead == NULL) {
		currentNode->lineHead = CreateLine(index);
	}
	else {
		Line* currentIndex = currentNode->lineHead;
		while (currentIndex->nextIndex != NULL) {
			currentIndex = currentIndex->nextIndex;
		}
		if (currentIndex->index != index) {
			currentIndex->nextIndex = CreateLine(index);
		}
	}
	return;
}
void WordBST::DeleteIndexAll() {
	Line* currentIndex = currentNode->lineHead;
	Line* nextIndex = currentIndex->nextIndex;
	while (nextIndex != NULL) {
		delete currentIndex;
		currentIndex = nextIndex;
		nextIndex = currentIndex->nextIndex;
	}
}
void WordBST::DeleteNoChildNode() {
	if (rootNode == currentNode) { //단일 노드인 경우
		return;
	}
	if (parentNode->leftChild == currentNode) {
		parentNode->leftChild = NULL;
	}
	else {
		parentNode->rightChild = NULL;
	}
}
void WordBST::DeleteOneChildNode() {
	Node* childNode;
	if (currentNode->leftChild == NULL) {
		childNode = currentNode->rightChild;
	}
	else {
		childNode = currentNode->leftChild;
	}
	//삭제할 노드가 루트 노드일 경우 루트 노드를 변경하고 종료
	if (rootNode == currentNode) {
		rootNode = childNode;
		return;
	}
	if (parentNode->leftChild == currentNode) {
		parentNode->leftChild = childNode;
	}
	else {
		parentNode->rightChild = childNode;
	}
}
void WordBST::DeleteTwoChildNode() {
	//오른쪽 서브 트리의 가장 큰 값을 계승자(대체될 노드)로 만들어 현재 노드를 대체
	Node* successor = currentNode->rightChild;
	parentNode = currentNode; 
	while (successor->leftChild != NULL) {
		parentNode = successor;
		successor = successor->leftChild;
	}
	//대체될 노드의 값을 복사
	currentNode->word = successor->word; 
	DeleteIndexAll();
	currentNode->lineHead = successor->lineHead;
	successor->lineHead = NULL;
	//successor 노드에 대한 삭제
	currentNode = successor;
	DeleteOneChildNode();
}
WordBST::WordBST() {
	rootNode = NULL;
	currentNode = NULL;
	parentNode = NULL;
}
WordBST::~WordBST() {
	DeleteWordBSTAll(rootNode);
}
WordBST::Node* WordBST::CreateNode(std::string word) {
	Node* newNode = new Node;
	newNode->leftChild = NULL;
	newNode->lineHead = NULL;
	newNode->word = word;
	newNode->rightChild = NULL;
	return newNode;
}
void WordBST::AddWordBST(std::string word, int index) {
	if (!IsInWordBST(word)) {
		currentNode = CreateNode(word);
		if (rootNode != NULL) {
			if (parentNode->word > word) {
				parentNode->leftChild = currentNode;
			}
			else {
				parentNode->rightChild = currentNode;
			}
		}
		else {
			rootNode = currentNode;
		}
	}
	AddIndex(index);
}
void WordBST::DeleteWordBSTNode(std::string word) {
	if (!IsInWordBST(word)) {
		return; //예외처리 가능하면 하기
	}
	else {
		if (currentNode->leftChild == NULL && currentNode->rightChild == NULL) {
			DeleteNoChildNode();
		}
		else if (currentNode->leftChild == NULL || currentNode->rightChild == NULL) {
			DeleteOneChildNode();
		}
		else {
			DeleteTwoChildNode();
		}
		DeleteIndexAll(); //string은 해제 안 해줘도 소멸자가 동작할까????
		delete currentNode; //삭제할 노드 동적 할당 해제
	}
}
void WordBST::DeleteWordBSTAll(Node* iter) {
	//후위순회
	if (iter != NULL) { 
		DeleteWordBSTAll(iter->leftChild);
		DeleteWordBSTAll(iter->rightChild);
		delete iter;
	}
}
bool WordBST::InputFile(const char* file, Hash& hashTable) {
	std::ifstream ifs(file);
	if (ifs.fail()) {
		return false;
	}
	std::string line, word;
	for (int index = 0; std::getline(ifs, line); index++) { //종료 조건 점검할 것
		std::vector<std::string> token = Tokenize(line);
		for (auto& word : token) {
			for (auto& lower : word) lower = tolower(lower);
			if (!hashTable.IsInHashTable(word)) {
				AddWordBST(word, index);
			}
		}
	}
	return true;
}
std::vector<std::string> Tokenize(std::string line) {
	std::regex delimiter(R"([\s|!|\?|.|,|(|)]+)");
	std::sregex_token_iterator it{ line.begin(), line.end(), delimiter, -1 };
	std::vector<std::string> tokenized{ it, {} };
	tokenized.erase(std::remove_if(tokenized.begin(), tokenized.end(), [](std::string const& s) {
		return s.size() == 0;
		}), tokenized.end());
	return tokenized;
}
bool WordBST::Output(std::ostream& os) {
	/*구현 - try문으로 파일 입출력 오류 같은 거 잡기*/
	Node* iter = rootNode;
	PrintWordIndex(iter, os);
	return true;
}
void WordBST::PrintWordIndex(Node* iter, std::ostream& os) {
	if (iter != NULL) {
		PrintWordIndex(iter->leftChild, os);
		if (iter->word.size() < 8) {
			os << iter->word << "\t\t";
		}
		else {
			os << iter->word << '\t';
		}
		currentIndex = iter->lineHead;
		os << currentIndex->index;
		currentIndex = currentIndex->nextIndex;
		while (currentIndex != NULL) {
			os << ", " << currentIndex->index;
			currentIndex = currentIndex->nextIndex;
		}
		os << '\n';
		PrintWordIndex(iter->rightChild, os);
	}
}
// TODO: 주석 달기, 함수 순서 조정, 클린 코드 만들기