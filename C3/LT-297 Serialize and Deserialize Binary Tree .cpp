//
// Created by Ke Ye on 2019-07-20.
//

#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

//First use preorder to serialize, then use preorder to build..
class Codec_1{
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };


    string serialize(TreeNode* root) {
        if(!root) return "# ";
        return to_string(root->val) + " " + serialize(root->left) + serialize(root->right);
    }

    TreeNode* helper(istringstream& str){
        string cur;
        str >> cur;
        if(cur == "#"){
            return nullptr;
        }
        else{
            TreeNode *root = new TreeNode(stoi(cur));
            root->left = helper(str);
            root->right = helper(str);
            return root;
        }
    }

    TreeNode* deserialize(string data) {
        istringstream str(data);
        return helper(str);
    }
};


//BFS

class Codec_2{
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };


    string serialize(TreeNode* root) {
        string res;
        queue<TreeNode*> bfs;
        bfs.push(root);
        while(!bfs.empty()){
            TreeNode *cur = bfs.front(); bfs.pop();
            if(cur){
                res += to_string(cur->val) + " ";
                bfs.push(cur->left);
                bfs.push(cur->right);
            }
            else{
                res += "# ";
            }
        }
        return res;
    }


    TreeNode* deserialize(string data) {
        istringstream str(data);
        string cur;
        str >> cur;
        TreeNode *root;
        if(cur == "#"){
            return nullptr;
        }
        else{
            root = new TreeNode(stoi(cur));
        }

        queue<TreeNode*> bfs;
        bfs.push(root);
        string l;
        string r;
        while(!bfs.empty()){
            TreeNode *cur = bfs.front(); bfs.pop();
            str >> l;
            str >> r;
            TreeNode *left = nullptr;
            TreeNode *right = nullptr;
            if(l != "#"){
                left = new TreeNode(stoi(l));
                bfs.push(left);
            }
            if(r != "#"){
                right = new TreeNode(stoi(r));
                bfs.push(right);
            }
            cur->left = left;
            cur->right = right;
        }
        return root;
    }
};







int main() {

}