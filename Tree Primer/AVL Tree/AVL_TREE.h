#pragma once
#include "AVL_Node.h";
#include <iostream>

class AVL_TREE
{
	public:
		AVL_TREE(Node* node = nullptr) :head(node) {};
		bool contains(int num);
		void insertNode(int val);
		void deleteNode(int num);
		Node* rebalance(Node* node, int val);
		int getBalance(Node* node);
		int getHeight(Node* node);
		int newHeight(Node* node);
		Node* LeftRotation(Node* node);
		Node* RightRotation(Node* node);
		Node* LeftRight(Node* node);
		Node* RightLeft(Node* node);

		friend std::ostream& operator<<(std::ostream& os, AVL_TREE tree);

	private:
		Node* head;
};
