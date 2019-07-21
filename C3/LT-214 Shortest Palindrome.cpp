//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>
#include <vector>

using namespace std;

//I think we can use longest common prefix to solve the problem
//WHich is ...reverse the original string and assign it to a new one.
//Then get the longest common prefix, which means we find a longest subpalindrome here. then we just need to add
//others left
//But still On^2.. since it's dp is n^2.. Emmmm

//They use a KMP to put original and reverse one together... So we just use KMP for new string here.
class Solution {
public:
    string shortestPalindrome(string s) {
        string tmp = s;
        reverse(tmp.begin(), tmp.end());
        string new_str = s + "#" + tmp;

        vector<int> f(new_str.length(), -1);
        int j = -1;
        int i = 0;
        while(i < new_str.length() - 1){
            if(j == -1 || new_str[i] == new_str[j]){
                i++;
                j++;
                f[i] = j;
            }
            else{
                j = f[j];
            }
        }
        string res = tmp.substr(0, tmp.length() - f.back() - 1) + s;
        return res;
    }
};

//can not do it directly with two strings... Since the first part of KMP only used for the pattern itself
//If two stirngs are not same... Then the f we generate will be wrong...
//Since when we combine them together, when we find failuer here, we chosse next[j]. but here next[j] is in
//the new string combined with two stirngs.... So here is a trick.... Emmm Well, I can not come up with it.. LOL

int main() {

}