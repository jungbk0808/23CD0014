#include <iostream>
#include <vector>
#include "WordIndex.h"
using namespace std;

// TODO: input file ������ ����, output file ������ ����
// �Ʒ� define�� ���ξ�� ����� ���� ���ϴ� �������� �������� ������ ��??
#define INPUT_FILE_NAME "input_file1.txt"
#define OUTPUT_FILE_NAME "output_file1.txt"

int main() {
	Hash hashTable;
	//hashTable.PrintHashTable();

	// TODO: ���� ���Ͽ� ���� �׽�Ʈ, �ܾ� ���� Ʈ���� ���� ����
	WordBST WordIndex;
	if (WordIndex.InputFile(INPUT_FILE_NAME, hashTable)) {
		ofstream o(OUTPUT_FILE_NAME);
		WordIndex.Output(o);
	}

	return 0;
}