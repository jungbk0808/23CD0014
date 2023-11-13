#include <iostream>
#include "WordIndex.h"
using namespace std;

#define INPUT_FILE_NAME "input_file2.txt"
#define OUTPUT_FILE_NAME "output_file1.txt"

int main() {
	Hash hashTable;

	WordBST WordIndex;
	if (WordIndex.InputFile(INPUT_FILE_NAME, hashTable)) {
		ofstream ofs(OUTPUT_FILE_NAME);
		ofs << "---word index---\n";
		WordIndex.Output(ofs);
	}
	return 0;
}