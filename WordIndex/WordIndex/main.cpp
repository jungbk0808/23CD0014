#include <iostream>
#include <vector>
#include "WordIndex.h"
using namespace std;

// TODO: input file 여러개 생성, output file 여러개 생성
// 아래 define은 접두어로 만들고 숫자 더하는 형식으로 여러개도 괜찮을 듯??
#define INPUT_FILE_NAME "input_file1.txt"
#define OUTPUT_FILE_NAME "output_file1.txt"

int main() {
	Hash hashTable;
	//hashTable.PrintHashTable();

	// TODO: 여러 파일에 대한 테스트, 단어 이진 트리의 균형 여부
	WordBST WordIndex;
	if (WordIndex.InputFile(INPUT_FILE_NAME, hashTable)) {
		ofstream o(OUTPUT_FILE_NAME);
		WordIndex.Output(o);
	}

	return 0;
}