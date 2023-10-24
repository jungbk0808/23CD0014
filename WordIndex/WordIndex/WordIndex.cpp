#include "WordIndex.h"

const std::string nullString = std::string("");

void Hash::InitHashTable() {
	hashWordsCount = 0;
	hashTable = new std::string[hashTableSize];
	for (int i = 0; i < hashTableSize; i++) {
		hashTable[i] = nullString; //�� string���� �ʱ�ȭ
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
	/*����*/
}
bool Hash::IsInHashTable(std::string word) {
	if (word.size() <= maxWordLength) {
		int hashValue = HashFunction(word);
		int index = hashValue;
		do {
			if (hashTable[index] == word) {
				return true;
			}
			else if (hashTable[index] == nullString) {
				break;
			}
			index = (index + 1) % hashTableSize;
		} while (index == hashValue);
	}
	return false;
}
int Hash::HashFunction(std::string word) {
	int hashValue = 0;
	int wordSize = word.size();
	for (int i = 0; i < wordSize; i++) {
		hashValue += word[i];
	}
	return hashValue;
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
void WordBST::AddIndex(int index) {
	if (currentNode == NULL) return;

	Line* newIndex = new Line;
	newIndex->index = index;
	newIndex->nextIndex = NULL;

	Line* currentIndex = currentNode->lineHead;
	while (currentIndex != NULL) {
		currentIndex = currentIndex->nextIndex;
	}
	currentIndex->nextIndex = newIndex;
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
	if (rootNode == currentNode) { //���� ����� ���
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
	//������ ��尡 ��Ʈ ����� ��� ��Ʈ ��带 �����ϰ� ����
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
	//������ ���� Ʈ���� ���� ū ���� �����(��ü�� ���)�� ����� ���� ��带 ��ü
	Node* successor = currentNode->rightChild;
	parentNode = currentNode; 
	while (successor->leftChild != NULL) {
		parentNode = successor;
		successor = successor->leftChild;
	}
	//��ü�� ����� ���� ����
	currentNode->word = successor->word; 
	DeleteIndexAll();
	currentNode->lineHead = successor->lineHead;
	successor->lineHead = NULL;
	//successor ��忡 ���� ����
	currentNode = successor;
	DeleteOneChildNode();
}
WordBST::WordBST() {
	rootNode = NULL;
	currentNode = NULL;
	parentNode = NULL;
}
void WordBST::AddWordBST(std::string word, int index) {
	if (!IsInWordBST(word)) {
		Node* newNode = new Node;
		newNode->leftChild = NULL;
		newNode->lineHead = NULL;
		newNode->word = word;
		newNode->lineHead = NULL;

		currentNode = newNode;
		if (parentNode->word > word) {
			parentNode->leftChild = currentNode;
		}
		else {
			parentNode->rightChild = currentNode;
		}
	}
	AddIndex(index);
}
void WordBST::DeleteWordBSTNode(std::string word) {
	if (!IsInWordBST(word)) {
		return; //����ó�� �����ϸ� �ϱ�
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
		DeleteIndexAll(); //string�� ���� �� ���൵ �Ҹ��ڰ� �����ұ�????
		delete currentNode; //������ ��� ���� �Ҵ� ����
	}
}
void WordBST::DeleteWordBSTAll() {
	//������ȸ
}
WordBST::~WordBST() {
	DeleteWordBSTAll();
}
bool InputFile(const char* file) {
	std::ifstream ifs(file);
	if (ifs.fail()) {
		return false;
	}
	std::string line, word;
	for (int index = 0; std::getline(ifs, line); index++) { //���� ���� ������ ��
		for (auto word : Tokenize(line)) {
			//�ؾ� �� ��
			/*����*/
		}
	}

	return true;
}
std::vector<std::string> Tokenize(std::string line) {
	std::regex delimiter(R"([\s|!|\?|.|,]+)");
	std::sregex_token_iterator it{ line.begin(), line.end(), delimiter, -1 };
	std::vector<std::string> tokenized{ it, {} };
	tokenized.erase(std::remove_if(tokenized.begin(), tokenized.end(), [](std::string const& s) {
		return s.size() == 0;
		}), tokenized.end());
	return tokenized;
}
bool Output(std::ostream& os) {
	/*����*/
	return true;
}