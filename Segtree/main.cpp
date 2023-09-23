#include "Segtree.h"
#include <iostream>
using namespace std;

#define LIST_LEN 8

int main() {
	int list[LIST_LEN] = { 21, 7, 8, 19, 2, 9, 6, 10 };
	int* seg_tree = Seg_tree_const(list, LIST_LEN);
	int q_s, q_e;
	cout << "------����Ʈ�� �κ� �� ����-----\n";
	while (true) {
		try {
			cout << "���� �ε��� : "; cin >> q_s;
			cout << "������ �ε��� : "; cin >> q_e;
			cout << "���� ������ �κ� �� : " << Get_query(seg_tree, LIST_LEN, q_s, q_e) << '\n';
			break;
		}
		catch (int) {
			cout << "����Ʈ�� ������ ��� �����Դϴ�.\n";
		}
	}
	int i, value;
	cout << "----------����Ʈ�� ����---------\n";
	while (true) {
		try {
			cout << "������ �ε��� : ";  cin >> i;
			if (i < 0 || i > LIST_LEN) throw i;
			break;
		}
		catch (int) {
			cout << "������ �ε����� ����Ʈ�� ������ ������ϴ�.\n";
		}
	}
	cout << "������ �� : "; cin >> value;
	Segtree_update(seg_tree, 0, LIST_LEN - 1, i, value - list[i], 0);
	cout << "������ ����Ʈ�� ���� ���� �κ� �� : " << Get_query(seg_tree, LIST_LEN, q_s, q_e);
	return 0;
}