//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
int _=[](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return 0;
}();
//Basic solution, but add BST rule here. since for node in bst, it should > left and < right
//So if we do preorder for original tree, then when we build the tree, we can use such rule to save much space.
//And here is a method that using 4byts node...
//Since in BST, we can only care about the number(the rule above), and assume the number won't exceed a range
//Then we can use a simple 4bytes string to describe the node.. Save space
//For example assume the number is below 2 ^ 31 - 1 here we use 32 bits >> 4bytes to describe a number
//So if we have XXXXXXXX XXXXXXXX XXXXXXXX XXXXXXXX. then for each, is a 1 byte number. fron 0 - 255
//So this is a good chance for us to use a 0-255 character to stand for that number. then finally each number can be
//compressed into 4 bytes and not like general ways 12138 >> "12138" 5 bytes.
//Try it

// class Codec {
// public:

//     // Encodes a tree to a single string.
//     // Preorder to serialize, and use BST rule to save space
//     string serialize(TreeNode* root) {
//         if(!root) return "";
//         return to_string(root->val) + " " + serialize(root->left) + serialize(root->right);
//     }

//     // Decodes your encoded data to tree.

//     TreeNode* helper(vector<int>& nums, int& idx, int left, int right){
//         if(idx == nums.size() || nums[idx] <= left || nums[idx] >= right) return nullptr;

//         TreeNode *root = new TreeNode(nums[idx++]);
//         root->left = helper(nums, idx, left, root->val);
//         root->right = helper(nums, idx, root->val, right);
//         return root;
//     }


//     TreeNode* deserialize(string data) {
//         if(data.empty()) return nullptr;
//         istringstream str(data);
//         string tmp;
//         vector<int> nums;
//         while(str >> tmp){
//             nums.push_back(stoi(tmp));
//         }
//         int idx = 0;
//         return helper(nums, idx, INT_MIN, INT_MAX);
//     }
// };

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));



//If use 4 bytes method, we should take care of the sign....
//If this is a negative number ... if we don't transform it to unsigned.
//Then it appears as completement code in memory. then there is mistake....
//Also when we go back from string. change it to unsigned char... or if the first digit is 1... it will be minus
//number ... then wrong..
class Codec{
public:
    string serialize(TreeNode* root) {
        if(!root) return "";
        string cur(4, ' ');
        for(int i = 0; i < 4; i++){
            cur[i] = (unsigned int)root->val >> ((3 - i) * 8);
        }
        return cur + serialize(root->left) + serialize(root->right);
    }

    TreeNode* helper(string& data, int& idx, int left, int right){
        if(idx == data.length()) return nullptr;
        int num = 0;
        for(int i = 0; i <= 3; i++){
            num += (unsigned char)data[idx + i] << ((3 - i) * 8);
        }
        if(num <= left || num >= right) return nullptr;
        idx += 4;
        TreeNode *root = new TreeNode(num);
        root->left = helper(data, idx, left, num);
        root->right = helper(data, idx, num, right);
        return root;
    }


    TreeNode* deserialize(string data) {
        int idx = 0;
        return helper(data, idx, INT_MIN, INT_MAX);
    }
};









int main () {

}