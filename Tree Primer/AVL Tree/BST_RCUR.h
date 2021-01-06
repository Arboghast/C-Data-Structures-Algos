#pragma once
#include "Node.h";
#include <iostream>

class BST_RCUR {
	public:
		BST_RCUR(Node* node = nullptr) :head(node), traverseMode(0) {};
		void insertNode(int num);
		void deleteNode(int num);
		bool contains(int num);
		void setMode(int num);

		friend std::ostream& operator<<(std::ostream& os, BST_RCUR tree);
	private:
		Node* head;
		int traverseMode;
};
