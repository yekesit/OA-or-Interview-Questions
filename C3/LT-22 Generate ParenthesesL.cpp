//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution{
public:
    vector<string> generateParenthesis(int n) {
        int left = 0, right = 0;
        vector<string> res;
        string cur;
        helper(res, cur, left, right, n);
        return res;
    }

private:
    void helper(vector<string>& res, string& cur, int& left, int& right, int n){
        if(left == n && right == n){
            res.push_back(cur);
            return;
        }

        if(left < n){
            cur += '(';
            left++;
            helper(res, cur, left, right, n);
            cur.pop_back();
            left--;
        }

        if(right < left){
            cur += ')';
            right++;
            helper(res, cur, left, right, n);
            cur.pop_back();
            right--;
        }
    }
};


int main(){

}