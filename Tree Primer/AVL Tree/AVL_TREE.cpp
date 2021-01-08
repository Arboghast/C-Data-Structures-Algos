#include "AVL_TREE.h"
#include <queue>
#include <functional>

using func_i = std::function<Node*(Node*)>;

std::ostream& operator<<(std::ostream& os, AVL_TREE tree) //same Methodology as BST, traversal methods are unchanged
{
    std::queue<Node*> bfs;
    if(tree.head)
        bfs.push(tree.head);
    bfs.push(nullptr);

    while (!bfs.empty()) {
        Node* node = bfs.front();
        if (node) {
            os << node->val << ":" << node->height << " ";
            if (node->left)
                bfs.push(node->left);
            if (node->right)
                bfs.push(node->right);
        }
        else {
            if (bfs.size() > 1) 
                bfs.push(nullptr);
            os << '\n';
        }
        bfs.pop();
    }
    return os;
}

bool AVL_TREE::contains(int num) //same methodology as a BST
{
    Node* node = head;
    while (node) {
        if (node->val == num)
            return true;
        else if (node->val < num)
            node = node->right;
        else
            node = node->left;
    }
    return false;
}

void AVL_TREE::insertNode(int val)
{
    func_i recurse = [&](Node* node)->Node* {  //step 1: recursive backtracking to all nodes from new node to root. Inserting nodes BST style
        if (!node)
            return new Node(val);
        else if (node->val < val)
            node->right = recurse(node->right);
        else
            node->left = recurse(node->left);

        node->height = newHeight(node); //step 2: update height of all nodes from new node to root

        return rebalance(node,val); //rebalance if necessary, by nature of an avl tree, only one rebalance operation will be taken, if any.
    };

    if (!head)
        head = new Node(val);
    else
        recurse(head);
}

void AVL_TREE::deleteNode(int val)
{
    func_i recurse = [&](Node* node)->Node* {
        Node* left = node->left;
        Node* right = node->right;
        if (left && left->val == val || right && right->val == val) {
            return deleteCases(node,val);
        }
        else if (node->val < val) {
            if(node->right)
                node->right = recurse(node->right);
        }
        else if (node->left){
            node->left = recurse(node->left);
        }

        node->height = newHeight(node);

        return rebalance(node,val);
    };

    if (head)
        recurse(head);
}

Node* AVL_TREE::deleteCases(Node* node, int val) {
    Node* left = node->left;
    Node* right = node->right;
    Node* target = nullptr;
    if (left && left->val == val) //find node to be deleted
        target = left;
    else if (right && right->val == val)
        target = right;

    if (target && (!target->left && !target->right)) {//Case 1: Leaf Nodes
        if (node->left == target) {
            delete target;
            node->left = nullptr;
        }
        else {
            delete target;
            node->right = nullptr;
        }
        return node;
    }
    else if (target && !target->left && target->right) {//Case 2a: One-child - Right
        if (node->left == target) {
            node->left = target->right;
            delete target;
        }
        else {
            node->right = target->right;
            delete target;
        }
        return node;
    }
    else if (target && target->left && !target->right) {//Case 2b: One-child - Left
        if (node->left == target) {
            node->left = target->left;
            delete target;
        }
        else {
            node->right = target->left;
            delete target;
        }
        return node;
    }
    else { //Case 3: Two-children
        func_i recurse = [&](Node* node)->Node* { //locate greatest predecessor with recursive backtracking for rebalancing
            if (node && node->right && !node->right->right) {
                Node* temp = node->right;
                target->val = temp->val;
                Node* temp2 = temp->left;
                delete node->right;
                node->right = temp2;
            }
            else if (node)
                node->right = recurse(node->right);

            if(node)
                node->height = newHeight(node);
            int tempVal = (target->right->val) ? (target->right->val) : (target->left->val);
            return rebalance(node, val);
        };

        Node* leftNode = target->left;
        if (!leftNode->right) {
            Node* temp = leftNode->left;
            target->val = leftNode->val;
            delete target->left;
            target->left = temp;

            node->height = newHeight(target);
            int tempVal = (temp && temp->val) ? (temp->val) : (target->right->val);
            return rebalance(target, tempVal);
        }
        else {
            return recurse(target->left);
        }
    }
}

Node* AVL_TREE::rebalance(Node* node, int val) //orient itself towards the new node added to choose which rotation is appropriate
{
    int bal = getBalance(node);
    if (bal > BALANCE_FACTOR) //right heavy
    {
        if (node->val < val) //right subtree left heavy
            return RightLeft(node);
        else
            return RightRotation(node);
    }
    else if(bal < -1*BALANCE_FACTOR){ //left heavy
        if (node->val < val) //left subtree right heavy
            return LeftRight(node);
        else
            return LeftRotation(node);
    }
    else {
        return node;
    }
}

int AVL_TREE::getBalance(Node* node) {
    return (!node) ? (0) : (getHeight(node->right) - getHeight(node->left));
}

//Balance Factor Equation: BF(Node N) = Height(N->right) - Height(N->left)  [order does not matter]
int AVL_TREE::getHeight(Node* node)
{
    return (!node) ? (-1) : (node->height); //height of a leaf node has to be 0, therefore its equation would be -1 - -1 = 0, which is why we return -1
}

int AVL_TREE::newHeight(Node* node) 
{
    if (!node)
        return -1;
    return std::max(getHeight(node->left), getHeight(node->right)) + 1;
}

Node* AVL_TREE::RightLeft(Node* node) //Right subtree - Skewed to the left -consolidate to one side and rotate
{
    if (node && node->right) {
        node->right = RightRotation(node->right);
        return LeftRotation(node);
    }
}

Node* AVL_TREE::LeftRight(Node* node) //Left subtree - Skewed to the right -consolidate to one side and rotate
{
    if (node && node->left) {
        node->left = LeftRotation(node->left);
        return RightRotation(node);
    }
}

Node* AVL_TREE::LeftRotation(Node* node) //Left Rotation
{
    if (node && node->right) {
        Node* newhead = node->right; //b becomes new head
        node->right = newhead->left; //a adopts b's left children as its right child
        newhead->left = node; //b adopts a as its left child

        node->height = newHeight(node); //recalculate height for rotated nodes, it's unneccesary to change its children node's heights
        newhead->height = newHeight(newhead);
        return newhead;
    }
}

Node* AVL_TREE::RightRotation(Node* node) 
{
    if (node && node->left) {
        Node* newhead = node->left;
        node->left = newhead->right;
        newhead->right = node;
        
        node->height = newHeight(node); //recalculate height for rotated nodes, it's unneccesary to change its children node's heights
        newhead->height = newHeight(newhead);
        return newhead;
    }
}
