#pragma once

struct Node { //total 12 bytes of memory - efficient ordering of data members
	int val; //sizeof(int) == 4
	Node* left; //sizeof(pointer) ==  4 (size of pointer depends on processor architecture - 32bit vs 64bitvs etc..
	Node* right;  //sizeof(pointer) == 4
	Node(int v = 0) :val(v), left(nullptr), right(nullptr) {};
};
