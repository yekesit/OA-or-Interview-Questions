//
// Created by Ke Ye on 2019-06-23.
//

#include <iostream>
#include <vector>
#include <set>


using namespace std;


struct cmp{
    bool operator()(const pair<int, int>& p1, const pair<int, int>& p2) const{
        return p1.first < p2.first;
    }
};

vector<int> maxSubarray(vector<int>& nums, int m){
    set<pair<int, int>, cmp> pre_idx;
    int pre = 0;
    int max_mod = 0;
    int start = 0;
    int end = 0;
    for(int i = 0; i < nums.size(); i++){
        pre = (pre + nums[i]) % m;
        if(max_mod < pre) {
            max_mod = max(max_mod, pre);
            start = 0;
            end = i;
        }
        pre_idx.insert({pre, i});
        auto it = pre_idx.lower_bound({pre + 1, i});
        if(it != pre_idx.end()){
            int cur = (pre - it->first + m) % m;
            if(cur > max_mod){
                max_mod = cur;
                start = it->second + 1;
                end = i;
            }
        }
    }
    vector<int> res(nums.begin() + start, nums.begin() + end + 1);
    return res;
}

int main() {
    vector<int> arr{3, 3, 5, 6, 7, 9};
    int m = 5;
    vector<int> res = maxSubarray(arr, m);
    for(auto r : res)
        cout << r << ' ';
}