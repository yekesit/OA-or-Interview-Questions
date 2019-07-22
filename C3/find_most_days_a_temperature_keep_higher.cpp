//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>
#include <vector>
#include <stack>

using namespace std;


vector<int> findDaysHigherBefore(vector<int>& input){
    stack<int> idx;
    vector<int> res(input.size());
    for(int i = input.size() - 1; i >= 0; i--){
        while(!idx.empty() && input[i] > input[idx.top()]){
            int cur = idx.top(); idx.pop();
            res[cur] = cur - i - 1;
        }
        idx.push(i);
    }
    int i = -1;
    while(!idx.empty()){
        int cur = idx.top(); idx.pop();
        res[cur] = cur - i - 1;
    }
    return res;
}


int main (){
    vector<int> input{13,21,18,27,23,25};

    vector<int> res = findDaysHigherBefore(input);
    for(auto& r : res)
        cout << r << ' ';
}