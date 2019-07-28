//
// Created by Ke Ye on 2019-07-27.
//

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<int> findTwoNumber(vector<int>& num1, vector<int>& num2, int k){
    int max_res = INT_MIN;
    int size1 = num1.size();
    int size2 = num2.size();
    int idx1 = 0;
    int idx2 = size2 - 1;
    vector<int> res(2, -1);
    while(idx1 < size1 && idx2 >= 0){
        if(num1[idx1] + num2[idx2] <= k){
            if(num1[idx1] + num2[idx2] == k){
                return {idx1, idx2};
            }
            if(max_res < num1[idx1] + num2[idx2]){
                max_res = num1[idx1] + num2[idx2];
                res[0] = idx1;
                res[1] = idx2;
            }
            idx1++;
        }
        else {
            idx2--;
        }
    }
    return res;
}


int main() {
    vector<int> num1{1, 4, 5, 7};
    vector<int> num2{10, 20, 30, 40};
    int k = 42;

    vector<int> res = findTwoNumber(num1, num2, k);
    cout << res[0] << ' ' << res[1] << endl;
}