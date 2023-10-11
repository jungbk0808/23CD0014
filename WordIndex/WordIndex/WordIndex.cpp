#include "WordIndex.h"

const std::string nullString = std::string("");

void Hash::InitHashTable() {
	hashWordsCount = 0; //�ؽ� ���̺��� �ܾ� ���� �ʱ�ȭ
	hashTable = new std::string[hashTableSize]; //���� �Ҵ�
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
void Hash::ExtensionHashTable() {
	std::string* oldHashTable = hashTable;
	int oldHashTableSize = hashTableSize;
	hashTableSize += HASH_TABLE_SIZE;
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

}
void Hash::DeleteHashTable() {

}
bool Hash::IsInHashTable(std::string word) {
	
	return true;
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
Node* CreateWordBST(std::string word, int index) {

	return NULL;
}
void AddWordBST(Node** root, std::string word, int index) {
	
}
void DeleteWordBSTAll(Node** root) {

}
void DeleteWordBSTNode(Node** root, std::string word) {

}
void AddIndex(Line* head) {

}
void DeleteIndexAll(Line* head) {

}
bool InputFile(const char* file) {
	std::ifstream ifs(file);
	if (ifs.fail()) { 
		return false; 
	}
	std::string line, word;
	for (int index = 0; std::getline(ifs, line) ; index++) { //���� ���� ������ ��
		for (auto word : Tokenize(line)) {
			//�ؾ� �� ��
			
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

	return true;
}