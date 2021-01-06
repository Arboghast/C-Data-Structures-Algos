#include "BST_ITR.h"
#include <queue>

void BST_ITR::insertNode(int val) {
	if (!head)
		head = new Node(val);
	else {
		Node* curr = head;
		while (curr) {
			if (curr->val == val)
				return;
			if (curr->val < val) {
				if (!curr->right) {
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

void BST_ITR::deleteNode(int val) {
	Node* prev = nullptr;
	Node* curr = head;
	while (curr) {
		if (curr->val == val){
			if (!curr->left && !curr->right) {//Case 1: Leaf Node
				if (!prev)						//edge case - root node
					head = nullptr;
				else
					(prev->left == curr) ? (prev->left = nullptr) : (prev->right = nullptr);
			}
			else if (curr->left && !curr->right || curr->right && !curr->left) { //Case 2: Move Children
				Node* child = (curr->left) ? (curr->left) : (curr->right);
				if (!prev)
					head = child;
				else
					(prev->left == curr) ? (prev->left = child) : (prev->right = child);
			}
			else {	//Case 3: Find Next Sucessor (vs Predecessor) (can do it either way)
				Node* target = curr;
				prev = curr;
				curr = curr->left;
				if (curr->right)
					prev->right = curr->left;
				else {
					while (curr->right) {
						prev = curr;
						curr = curr->right;
					}
					prev->left = curr->left;
				}
				target->val = curr->val;
			}
			delete curr;
			return;
		}
		else{
			prev = curr;
			(curr->val < val) ? (curr = curr->right) : (curr = curr->left);
		}
	}
}

bool BST_ITR::contains(int val) {
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

std::ostream& operator<<(std::ostream& os, BST_ITR tree) {//level based BST Tree Traversal: BFS 
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
