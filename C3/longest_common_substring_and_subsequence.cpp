//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>
#include <vector>

using namespace std;

// substring is different from subsequence

int LCSubstring(string& a , string& b){
    int row = a.length();
    int col = b.length();
    vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));
    int max_length = 0;
    for(int i = 1; i <= row; i++)
        for(int j = 1; j <= col; j++){
            if(a[i - 1] == b[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
                max_length = max(max_length, dp[i][j]);
            }
        }
    return max_length;
}


int LCSubsequence(string& a, string& b){
    int row = a.length();
    int col = b.length();
    vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));
    for(int i = 1; i <= row; i++)
        for(int j = 1; j <= col; j++){
            if(a[i - 1] == b[j - 1]){
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    return dp[row][col];
}


int main() {
    string a = "GeeksforGeeks";
    string b = "GeeksQuiz";

    cout << LCSubstring(a, b) << endl;

    string c = "AGGTAB";
    string d = "GXTXAYB";

    cout << LCSubsequence(c, d) << endl;
}