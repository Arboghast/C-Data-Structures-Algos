#pragma once
#include <ostream>
class BST
{
	public:
		struct Node {
			int val;
			Node* left;
			Node* right;
			Node(int v = 0) :val(v), left(nullptr), right(nullptr) {};
		};

		BST(BST::Node* h = nullptr) :head(h) {};
		void insertNode(int val);
		void deleteNode(int val);
		bool contains(int val);
		
		friend std::ostream& operator<<(std::ostream& os, BST tree);

	private:
		Node* head;
};

