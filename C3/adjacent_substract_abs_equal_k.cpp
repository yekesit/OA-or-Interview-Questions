//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>
#include <vector>

using namespace std;

void helper(vector<string>& res, string& cur, int target, int idx, int length){
    if(idx == length){
        if(target == 0){
            res.push_back(cur);
        }
        return;
    }

    for(char i = '0' ; i <= '9'; i++){
        if(abs(cur[idx - 1] - i) <= target){
            cur += i;
            helper(res, cur, target - abs(cur[idx - 1] - i), idx + 1, length);
            cur.pop_back();

        }
    }
}


vector<string> findNum(int length, int target){
    vector<string> res;
    string cur;
    for(char i = '1'; i <= '9'; i++) {
        cur += i;
        helper(res, cur, target, 1, length);
        cur.pop_back();
    }
    return res;
}




int main() {
    int length = 3;
    int target = 2;

    vector<string> res = findNum(length, target);
    for(auto& r : res)
        cout << r << endl;
}