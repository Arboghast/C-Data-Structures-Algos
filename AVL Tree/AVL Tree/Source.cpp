#include "BST.h"
#include <iostream>

using namespace std;

int main() {
	BST tree;
	tree.insertNode(2);
	tree.insertNode(4);
	tree.insertNode(5);
	tree.insertNode(1);
	tree.insertNode(3);
	tree.insertNode(7);
	tree.insertNode(6);

	cout << tree << endl << endl;
	cout << (int)tree.contains(3) << endl <<endl;
	//tree.deleteNode(5); Leaf Node Tests
	//tree.deleteNode(3);
	//tree.deleteNode(1);
	//tree.deleteNode(7); One Child Tests
	//tree.deleteNode(5);
	//tree.deleteNode(4); Two Child Tests
	cout << tree;
}