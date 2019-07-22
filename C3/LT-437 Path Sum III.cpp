//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>

using namespace std;

/Double DFS, do same thing for each substree from root
//n^2. slow. go again and again, do many duplicate operations.
// class Solution {
// public:
//     int pathSum(TreeNode* root, int sum) {
//         if(!root) return 0;
//         return subtree(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);

//     }

// private:
//     int subtree(TreeNode* root, int sum){
//         if(!root) return 0;
//         sum -= root->val;
//         return (sum == 0)  + subtree(root->left, sum) + subtree(root->right, sum);
//     }

// };


//See solution and learned one pass method.
//Use same thougth like what we do in array.. prefix and hashmap
//it's just here we should delete something if we go to another subtree...
//pretty fast!!! Nice


class Solution{
public:
    int pathSum(TreeNode* root, int sum){
        unordered_map<int, int> pre_sum;
        pre_sum[0] = 1;
        return subtree(root, pre_sum, sum, 0);
    }
private:
    int subtree(TreeNode* root, unordered_map<int, int>& pre_sum, int sum, int prefix){
        if(!root) return 0;
        root->val += prefix;
        int cur_res = pre_sum[root->val - sum];
        pre_sum[root->val]++;
        cur_res += subtree(root->left, pre_sum, sum, root->val);
        cur_res += subtree(root->right, pre_sum, sum, root->val);
        pre_sum[root->val]--; // Nice backtracking here.... change to another subtree
        return cur_res;
    }
};

int main() {

}