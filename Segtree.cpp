#include "Segtree.h"
#include <cmath>

int* Seg_tree_const(int* list, int n) {
	int height = (int)ceil(log2(n));
	int t_size = 2 * (int)pow(2, height) - 1;
	int* seg_tree = new int[t_size];
	Construct_tree(list, 0, n - 1, seg_tree, 0);
	return seg_tree;
}
int Construct_tree(int* list, int start, int end, int* seg_tree, int current) {
	if (start == end) {
		seg_tree[current] = list[start];
		return list[start];
	}
	int mid = (start + end) / 2;
	int child = 2 * current;
	seg_tree[current] = Construct_tree(list, start, mid, seg_tree, child + 1)
		+ Construct_tree(list, mid + 1, end, seg_tree, child + 2);
	return seg_tree[current];
}
int Get_query(int* seg_tree, int n, int q_s, int q_e) {
	if (q_s < 0 || q_e > n - 1 || q_s > q_e) {
		throw 0;
	}
	return Query_sum(seg_tree, 0, n - 1, q_s, q_e, 0);
}
int Query_sum(int* seg_tree, int start, int end, int q_s, int q_e, int current) {
	if (q_s <= start && q_e >= end) { //질의 범위에 완전히 포함되는 노드
		return seg_tree[current];
	}
	if (end < q_s || start > q_e) { //질의 범위를 벗어날 때
		return 0;
	}
	int mid = (start + end) / 2;
	int child = 2 * current;
	return Query_sum(seg_tree, start, mid, q_s, q_e, child + 1)
		+ Query_sum(seg_tree, mid + 1, end, q_s, q_e, child + 2);
}
int* Segtree_update(int* seg_tree, int start, int end, int i, int d_value, int current) {
	if (i < start || i > end) {
		return NULL;
	}
	seg_tree[current] = seg_tree[current] + d_value;
	if (start != end) {
		int mid = (start + end) / 2;
		int child = 2 * current;
		Segtree_update(seg_tree, start, mid, i, d_value, child + 1);
		Segtree_update(seg_tree, mid + 1, end, i, d_value, child + 2);
	}
	return seg_tree;
}