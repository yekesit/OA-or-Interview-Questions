//
// Created by Ke Ye on 2019-07-20.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int row = s1.length();
        int col = s2.length();
        vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));
        for(int i = 1; i <= col; i++){
            dp[0][i] += dp[0][i - 1] + s2[i - 1];
        }
        for(int i = 1; i <= row; i++){
            dp[i][0] += dp[i - 1][0] + s1[i - 1];
        }

        for(int i = 1; i <= row; i++)
            for(int j = 1; j <= col; j++){
                if(s1[i - 1] == s2[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else{
                    dp[i][j] = min(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
                }
            }
        return dp[row][col];
    }
};

int main() {

}
