#include "BST.h"
#include <queue>
#include <iostream>

using Node = BST::Node;

void BST::insertNode(int val)
{
	if (!head)
		head = new Node(val);
	else {
		Node* curr = head;
		while (curr) {
			if (curr->val == val)
				return;
			if (curr->val < val)
			{
				if (!curr->right)
				{
					curr->right = new Node(val);
					return;
				}
				curr = curr->right;
			}
			else {
				if (!curr->left) {
					curr->left = new Node(val);
					return;
				}
				curr = curr->left;
			}
		}
	}
}

void BST::deleteNode(int val)
{
	Node* prev = nullptr;
	Node* curr = head;
	while (curr) {
		if (curr->val == val){
			if (!curr->left && !curr->right) {//Case 1: Leaf Node
				if (!prev) { //edge case - root node
					head = nullptr;
					return;
				}
				else {
					(prev->left == curr) ? (prev->left = nullptr) : (prev->right = nullptr);
					return;
				}
			}
			else if (curr->left && !curr->right || curr->right && !curr->left) { //Case 2: Move Children
				Node* child = (curr->left) ? (curr->left) : (curr->right);
				if (!prev) {
					head = child;
					return;
				}
				else {
					(prev->left == curr) ? (prev->left = child) : (prev->right = child);
					return;
				}
			}
			else {	//Case 3: Find Next Sucessor vs Predecessor
				Node* itr_prev = nullptr;
				Node* itr = curr;
				bool tog = false;
				if (itr->left) {
					itr_prev = itr;
					itr = itr->left;
					while (itr->right) {
						itr_prev = itr;
						itr = itr->right;
						tog = true;
					}
					curr->val = itr->val;
					(tog)?(itr_prev->right = itr->left):(itr_prev->left = itr->left);
					delete itr;
					return;
				}
				else {
					itr_prev = itr;
					itr = itr->right;
					while (itr->left) {
						itr_prev = itr;
						itr = itr->left;
						tog = true;
					}
					curr->val = itr->val;
					(tog)?(itr_prev->left = itr->right):(itr_prev->right = itr->right);
					delete itr;
					return;
				}
			}
		}
		else if (curr->val < val){
			prev = curr;
			curr = curr->right;
		}
		else{
			prev = curr;
			curr = curr->left;
		}
			
	}
}

bool BST::contains(int val)
{
	Node* curr = head;
	while (curr) {
		if (curr->val == val)
			return true;
		else if (curr->val < val)
			curr = curr->right;
		else
			curr = curr->left;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, BST tree) //level based BST Tree Traversal: BFS
{
	std::queue<Node*> queue;
	queue.push(tree.head);
	queue.push(nullptr);

	while (!queue.empty()) {
		Node* temp = queue.front();
		if (!temp) {
			queue.pop();
			if (!queue.empty()) {
				os << std::endl;
				queue.push(nullptr);
			}
			else
				break;
		}
		else {
			if (temp->left)
				queue.push(temp->left);
			if (temp->right)
				queue.push(temp->right);
			queue.pop();
			os << temp->val << " ";
		}
	}

	return os;
}
