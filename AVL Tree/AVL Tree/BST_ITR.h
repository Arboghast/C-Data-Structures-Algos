#pragma once
#include <iostream>
#include "Node.h";

class BST_ITR {
	public:
		BST_ITR(Node* h = nullptr) :head(h) {};
		void insertNode(int val);
		void deleteNode(int val);
		bool contains(int val);
		
		friend std::ostream& operator<<(std::ostream& os, BST_ITR tree);
	private:
		Node* head;
};
