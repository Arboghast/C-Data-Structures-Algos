#pragma once

struct Node { //total 12 bytes of memory - efficient ordering of data members
	int val; //sizeof(int) == 4
	int height; //level of a node
	Node* left; //sizeof(pointer) ==  4 (size of pointer depends on processor architecture - 32bit vs 64bitvs etc..
	Node* right;  //sizeof(pointer) == 4
	Node(int v = 0, int h = 0) :val(v), height(h), left(nullptr), right(nullptr) {};
};
