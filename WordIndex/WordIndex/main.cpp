#include <iostream>
#include <vector>
#include "WordIndex.h"
using namespace std;

#define INPUT_FILE_NAME "input_file1.txt"
#define OUTPUT_FILE_NAME "output_file1.txt"

int main() {
	Hash hashTable;
	//hashTable.PrintHashTable();

	WordBST WordIndex;
	if (WordIndex.InputFile(INPUT_FILE_NAME, hashTable)) {
		WordIndex.Output();
	}

	return 0;
}