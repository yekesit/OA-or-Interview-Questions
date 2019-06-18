//
// Created by Ke Ye on 2019-06-18.
//

#include <iostream>
#include <stack>
#include <deque>

using namespace std;

// 2 * 3 + 5 - 4 / 2

//      -
//   +     /
//  * 5   4 2
// 2 3

struct TreeNode{
    string val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(string val) : val(val), left(nullptr), right(nullptr){}
};



int main() {
    string input = "2*3+5-4/2";
    deque<TreeNode*> build;
    char prev = ' ';
    for(int i = 0; i < input.length(); i++){
        if(input[i] >= '0' && input[i] <= '9'){
            build.push_back(new TreeNode(to_string(input[i])));
        }
        else{
            if(prev == ' '){
                build.push_back(new TreeNode(to_string(input[i])));
                prev = input[i];
            }
            else{
                TreeNode *cur = new TreeNode(to_string(input[i]));
                build.push_back(cur);
                if(prev == '*' || prev == '/'){
                    TreeNode* left = build.front(); build.pop_front();
                    TreeNode* mid = build.front(); build.pop_front();
                    TreeNode* right = build.front(); build.pop_front();
                    mid->left = left;
                    mid->right = right;
                    build.push_front(mid);
                    prev = input[i];
                }
            }
        }
    }
    while(build.size() > 1){
        TreeNode* left = build.front(); build.pop_front();
        TreeNode* mid = build.front(); build.pop_front();
        TreeNode* right = build.front(); build.pop_front();
        mid->left = left;
        mid->right = right;
        build.push_front(mid);
    }
    cout << build.front()->val << endl;

}