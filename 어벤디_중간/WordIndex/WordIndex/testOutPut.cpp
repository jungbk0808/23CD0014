#include <fstream>
#include <iostream>
using namespace std;

void OutPut(ostream& os) { //
	os << "hi" << endl;
}

int main() {
	ofstream ofs("text.txt");
	if (ofs.fail()) {
		cerr << "Error!" << endl;
	}
	OutPut(ofs);
}