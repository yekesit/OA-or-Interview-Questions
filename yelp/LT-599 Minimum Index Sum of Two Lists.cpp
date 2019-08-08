//
// Created by Ke Ye on 2019-08-08.
//


#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution{
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        unordered_map<string, int> idx1;
        for(int i = 0; i < list1.size(); i++){
            idx1[list1[i]] = i;
        }

        unordered_map<string, int> idx2;
        int min_sum = INT_MAX;
        for(int i = 0; i < list2.size(); i++){
            if(idx1.count(list2[i])){
                idx2[list2[i]] = i + idx1[list2[i]];
                min_sum = min(min_sum, idx2[list2[i]]);
            }
        }
        vector<string> res;
        for(auto& i : idx2){
            if(i.second == min_sum){
                res.push_back(i.first);
            }
        }

        return res;
    }
};

int main() {

}
