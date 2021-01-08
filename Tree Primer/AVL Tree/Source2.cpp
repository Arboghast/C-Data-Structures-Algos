#include <iostream>
#include "AVL_TREE.h";

using namespace std;

int main() {
	AVL_TREE test1;
	int vals [6] = { 3, 8, -2, 0, -1, 11 };
	for (int x : vals) {
		test1.insertNode(x);
		cout << test1 << endl;
	}

	int vol[3] = { -2, 8, -1 };
	for (int y : vol) {
		test1.deleteNode(y);
		cout << y << endl << test1 << endl;
		test1.insertNode(y);
	}
	
}