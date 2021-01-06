#include "AVL_TREE.h"

std::ostream& operator<<(std::ostream& os, AVL_TREE tree)
{
    return os;
}

bool AVL_TREE::search(int num)
{
    return false;
}

void AVL_TREE::insertNode(int num)
{


}

void AVL_TREE::deleteNode(int num)
{
    Node* node = head;
    Recurse(num,node);
}

void AVL_TREE::Recurse(int num, Node* node) {
    if (node) {
        if (node->val == num) {
            //delete
        }
        else if (node->val > num) {
            Recurse(num,node->left);
        }
        else {
            Recurse(num,node->right);
        }

        auto LRBalanceProp = [&](Node* node)->int {
            return height(node->left) - height(node->right);
        };

        auto RLBalanceProp = [&](Node* node)->int {
            return height(node->right) - height(node->left);
        };

        if (LRBalanceProp(node) > 1) //Left heavy : left subtree is larger than right
        {
            if (RLBalanceProp(node->left) > 1) //Left subtree is Right heavy
            {
                RLRotation(node);
            }
            else {
                RRRotation(node);
            }
        }
        else { //Right heavy : right subtree is larger than left
            if (LRBalanceProp(node->right) > 1) {  //Right subtree is left heavy
                LRRotation(node);
            }
            else {
                LLRotation(node);
            }
        }
    }
}

//Balance Factor Equation: BF(Node N) = Height(N->right) - Height(N->left)  [order does not matter]
int AVL_TREE::height(Node* node)
{
    return (!node) ? (-1) : (node->height); //height of a leaf node has to be 0, therefore its equation would be -1 - -1 = 0, which is why we return -1
}

void AVL_TREE::LRRotation(Node* node) //Right subtree - Skewed to the left
{
    if (node && node->right) {
        RRRotation(node->right);
        LLRotation(node);
    }
}

void AVL_TREE::RLRotation(Node* node) //Left subtree - Skewed to the right
{
    if (node && node->left) {
        LLRotation(node->left);
        RRRotation(node);
    }
}

void AVL_TREE::LLRotation(Node* node) //Left Rotation
{
    if (node && node->right) {
        Node* newhead = node->right; //b becomes new head
        node->right = newhead->left; //a adopts b's left children as its right child
        newhead->left = node; //b adopts a as its left child
    }
}

void AVL_TREE::RRRotation(Node* node) 
{
    if (node && node->left) {
        Node* newhead = node->left;
        node->left = newhead->right;
        newhead->right = node;
    }
}
