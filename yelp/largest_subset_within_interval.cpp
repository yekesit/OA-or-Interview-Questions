//
// Created by Ke Ye on 2019-07-27.
//

#include <iostream>
#include <vector>

using namespace std;

vector<int> findSubsetWithinInterval(vector<int>& num, int interval){
    sort(num.begin(), num.end());
    int prev_idx = 0;
    int max_len = 1;
    int left = 0;

    for(int i = 0; i <= num.size(); i++){
        if(i == num.size() || num[i] - num[prev_idx] > interval){
            if(max_len < i - prev_idx){
                max_len = i - prev_idx;
                left = prev_idx;
            }
            prev_idx = i;
        }
    }
    vector<int> res(num.begin() + left, num.begin() + left + max_len);
    return res;


}



int main() {
    vector<int> num{4, 3, 0, 15, 21};
    int k = 17;
    vector<int> res = findSubsetWithinInterval(num, k);
    for(auto& r : res){
        cout << r << ' ';
    }
}