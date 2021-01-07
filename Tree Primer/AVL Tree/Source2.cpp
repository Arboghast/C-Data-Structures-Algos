#include <iostream>
#include "AVL_TREE.h";

using namespace std;

int main() {
	AVL_TREE test1;
	int vals [5] = { 3, 8, -2, 0, -1 };
	for (int x : vals) {
		test1.insertNode(x);
		cout << test1 << endl;
	}
}