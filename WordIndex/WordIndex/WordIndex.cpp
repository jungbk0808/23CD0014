#include "WordIndex.h"

const std::string nullString = std::string("");

void Hash::InitHashTable() {
	hashWordsCount = 0; //해쉬 테이블의 단어 개수 초기화
	hashTable = new std::string[hashTableSize]; //동적 할당
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
	/*구현*/
}
void Hash::DeleteHashTable() {
	delete[] hashTable;
}
bool Hash::IsInHashTable(std::string word) {
	/*구현*/
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
	/*구현*/
	return NULL;
}
void AddWordBST(Node** root, std::string word, int index) {
	/*구현*/
}
void DeleteWordBSTAll(Node** root) {
	/*구현*/
}
void DeleteWordBSTNode(Node** root, std::string word) {
	/*구현*/
}
void AddIndex(Line* head) {
	/*구현*/
}
void DeleteIndexAll(Line* head) {
	/*구현*/
}
bool InputFile(const char* file) {
	std::ifstream ifs(file);
	if (ifs.fail()) { 
		return false; 
	}
	std::string line, word;
	for (int index = 0; std::getline(ifs, line) ; index++) { //종료 조건 점검할 것
		for (auto word : Tokenize(line)) {
			//해야 할 일
			/*구현*/
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
	/*구현*/
	return true;
}