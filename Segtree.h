#pragma once
int* Seg_tree_const(int* list, int n);
int Construct_tree(int* list, int start, int end, int* seg_tree, int current);
int Get_query(int* seg_tree, int n, int q_s, int q_e);
int Query_sum(int* seg_tree, int start, int end, int q_s, int q_e, int current);
int* Segtree_update(int* seg_tree, int start, int end, int i, int d_value, int current);