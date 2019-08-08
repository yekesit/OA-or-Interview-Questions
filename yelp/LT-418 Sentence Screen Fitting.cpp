//
// Created by Ke Ye on 2019-08-08.
//

#include <iostream>
#include <vector>

using namespace std;

// Review here. Since the filling task can be repetitive, so we should record some previous situation to save time
// if there are much more loops in the future.
class Solution{
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int num = 0;
        int size = sentence.size();
        vector<int> cnt(size);
        for(int i = 0; i < rows; i++){
            int cur_start = num % size;
            if(cnt[cur_start]){
                num += cnt[cur_start];
            }
            else{
                int len = 0;
                int cur_cnt = 0;
                int right = cur_start;
                while(len + sentence[right].size() <= cols){
                    len += sentence[right].size() + 1;
                    right = (right + 1) % size;
                    cur_cnt++;
                }
                // Can not use idx and right to get count directly since right can increase from size - 1 to 0....
                cnt[cur_start] = cur_cnt;
                num += cur_cnt;
            }
        }
        return num / size;
    }
};
int main() {

}