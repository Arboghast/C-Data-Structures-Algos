#include "BST_RCUR.h"
#include <functional>

using func_t = std::function<void (Node*)>;
using func_b = std::function<bool (Node*)>;
using func_n = std::function<Node* (Node*,Node*)>;

void BST_RCUR::insertNode(int num) {
	func_t recurse = [&](Node* node)->void {
		if (node->val < num) {
			if (node->right)
				return recurse(node->right);
			else
				node->right = new Node(num);
		}
		else if (node->val > num) {
			if (node->left)
				return recurse(node->left);
			else
				node->left = new Node(num);
		}
	};

	if (!head)
		head = new Node(num);
	else
		recurse(head);
}

void BST_RCUR::deleteNode(int num) {
	func_n predecessor = [&](Node* curr, Node* prev)->Node* {
		if (!curr->left)
			return prev;
		else
			return predecessor(curr->left, curr);
	};

	Node* target = nullptr; //way to "return" more than one value, modify out-of-scope
	func_n findNode = [&](Node* curr, Node* prev)->Node* {
		if (curr) {
			if (curr->val == num) {
				target = curr;
				return prev;
			}
			else if (curr->val > num)
				findNode(curr->left, curr);
			else
				findNode(curr->right, curr);
		}
	};
	
	Node* replacement = findNode(head,nullptr);
	if (target) {
		if (target->left && target->right) { //no children
			if (!target->right->left) {  //initial step edge case in finding predecessor
				target->val = target->right->val;
				target->right = target->right->right;
				delete target->right;
			}
			else {
				Node* chosenOne = predecessor(target->right, target);
				target->val = chosenOne->left->val;   //we know its on the left, implied by predecessor
				Node* temp = chosenOne->left->right;
				delete chosenOne->left;
				chosenOne->left = temp;
			}
		}
		else {
			Node* child;
			if (!target->left && !target->right) //slight if else statement optimization to reduce comparisions
				child = nullptr;
			else
				child = (target->right) ? (target->right) : (target->left);

			(replacement->right == target) ? (replacement->right = child) : (replacement->left = child);
		}
	}
}

bool BST_RCUR::contains(int num) {
	func_b recurse = [&](Node* node)->bool {
		if (node) {
			if (node->val == num)
				return true;
			else if (node->val < num)
				return recurse(node->right);
			else
				return recurse(node->left);
		}
		return false;
	};

	return recurse(head);
}

void BST_RCUR::setMode(int num) {
	traverseMode = num;
}

std::ostream& operator<<(std::ostream& os, BST_RCUR tree) {
	func_t preorder = [&](Node* node)->void {
		if (node) {
			os << node->val << " ";
			preorder(node->left);
			preorder(node->right);
		}
	};

	func_t inorder = [&](Node* node)->void { //print out values of the tree in numerical order strictly increasing
		if (node) {
			inorder(node->left);
			os << node->val << " ";
			inorder(node->right);
		}
	};

	func_t postorder = [&](Node* node)->void {
		if (node) {
			postorder(node->left);
			postorder(node->right);
			os << node->val << " ";
		}
	};

	if (tree.traverseMode == 0)
		preorder(tree.head);
	if (tree.traverseMode == 1)
		inorder(tree.head);
	if (tree.traverseMode == 2)
		postorder(tree.head);

	return os;
}
