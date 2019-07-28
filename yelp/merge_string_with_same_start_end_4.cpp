//
// Created by Ke Ye on 2019-07-27.
//

#include <iostream>

using namespace std;

//c_str >> string >> const char*
string mergeTwoString(string& s1, string& s2){
    int len = s1.length();
    for(int i = 0; i < len; i++){
        if(strncmp(s1.c_str() + i, s2.c_str(), len - i) == 0){
            return s1 + s2.substr(len - i);
        }
    }
    return s1 + s2;
}


int main() {
    string s1 = "abc";
    string s2 = "bcd";

    string res = mergeTwoString(s1, s2);
    cout << res << endl;
}