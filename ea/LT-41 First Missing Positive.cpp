//
// Created by Ke Ye on 2019-06-14.
//

#include <iostream>
#include <vector>

using namespace std;

//we can sort, we can use hashmap.
//The Best way is to put every number in its position.
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int size = nums.size();
        int i = 0;
        while(i < size){
            if(nums[i] <= 0 || nums[i] > size || nums[i] == i + 1 || nums[nums[i] - 1] == nums[i]){
                i++;
                continue;
            }
            else {
                swap(nums[nums[i] -  1], nums[i]);
            }
        }
        for(int i = 0; i < size; i++){
            if(nums[i] != i + 1) return i + 1;
        }
        return size + 1;
    }
};

int main(){

}