#include "Segtree.h"
#include <iostream>
using namespace std;

#define LIST_LEN 8

int main() {
	int list[LIST_LEN] = { 21, 7, 8, 19, 2, 9, 6, 10 };
	int* seg_tree = Seg_tree_const(list, LIST_LEN);
	int q_s, q_e;
	cout << "------리스트의 부분 합 질의-----\n";
	while (true) {
		try {
			cout << "시작 인덱스 : "; cin >> q_s;
			cout << "마지막 인덱스 : "; cin >> q_e;
			cout << "질의 범위의 부분 합 : " << Get_query(seg_tree, LIST_LEN, q_s, q_e) << '\n';
			break;
		}
		catch (int) {
			cout << "리스트의 범위를 벗어난 질의입니다.\n";
		}
	}
	int i, value;
	cout << "----------리스트의 갱신---------\n";
	while (true) {
		try {
			cout << "수정할 인덱스 : ";  cin >> i;
			if (i < 0 || i > LIST_LEN) throw i;
			break;
		}
		catch (int) {
			cout << "수정할 인덱스가 리스트의 범위를 벗어났습니다.\n";
		}
	}
	cout << "수정할 값 : "; cin >> value;
	Segtree_update(seg_tree, 0, LIST_LEN - 1, i, value - list[i], 0);
	cout << "수정된 리스트의 질의 범위 부분 합 : " << Get_query(seg_tree, LIST_LEN, q_s, q_e);
	return 0;
}