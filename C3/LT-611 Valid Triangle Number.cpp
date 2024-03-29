//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int size = nums.size();
        int res = 0;
        for(int i = 0; i < size - 2; i++){
            if(!nums[i]) continue;
            int left = i + 1;
            int right = i + 2;
            while(left < size - 1){
                while(right < size && nums[i] + nums[left] > nums[right]) right++;
                res += right - left - 1;
                left++;
            }
        }
        return res;
    }
};

int main() {

}