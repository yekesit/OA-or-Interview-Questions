//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>

using namespace std;

//First thougth is, use a previous pointer to save previous node
//Then  keep using previous->right = current node to build the whole list.
//But here are many redundant operations.. Emmmm
//Try to improve.
//Finish improvement. EMmmm Nice. for recursionm focus on current node... Emmm
// class Solution {
// public:
//     void flatten(TreeNode* root) {
//         if(!root) return;
//         p = root;
//         TreeNode *right = root->right;
//         helper(root->left);
//         root->left = nullptr;
//         helper(right);
//     }

// private:
//     TreeNode* p;
//     void helper(TreeNode* root){
//         // if(!root) return;
//         // p->right = root;
//         // p = root;
//         // TreeNode *right = root->right;
//         // p->right = p->left;
//         // p->left = nullptr;
//         // helper(p->right);
//         // helper(right);
//         if(!root) return;
//         p->right = root;
//         p = root;
//         TreeNode *right = root->right;
//         helper(root->left);
//         root->left = nullptr;
//         helper(right);
//     }
// };

//Also can do it in iteration.
//It's just, for every node, if we have left child. Then finally there is a node in left subtree
//which will finally connect to right child.
//So we can go to left child, and then find the most right child, then connect to the current node  right child
//Then resolve current node which is left > right and left = nullptr
//A little slow but code is concise and nice. EMmm

class Solution{
public:
    void flatten(TreeNode* root) {
        TreeNode *cur = root;
        while(cur){
            if(cur->left) {
                TreeNode *left = cur->left;
                while(left->right){
                    left = left->right;
                }
                left->right = cur->right;
                cur->right = cur->left;
                cur->left =nullptr;
            }
            cur = cur->right;
        }
    }
};


int main() {

}