#pragma once
#include "AVL_Node.h";
#include <iostream>

class AVL_TREE
{
	public:
		AVL_TREE(Node* node = nullptr) :head(node) {};
		bool search(int num);
		void insertNode(int num);
		void deleteNode(int num);
		int height(Node* node);
		void LLRotation(Node* node);
		void RRRotation(Node* node);
		void LRRotation(Node* node);
		void RLRotation(Node* node);

		void Recurse(int num, Node* node);

		friend std::ostream& operator<<(std::ostream& os, AVL_TREE tree);

	private:
		Node* head;
};
