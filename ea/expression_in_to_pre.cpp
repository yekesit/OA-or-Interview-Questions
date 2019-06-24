//
// Created by Ke Ye on 2019-06-23.
//

#include <iostream>
#include <stack>
#include <vector>
using namespace std;



//First method we can also build a tree from inorder. then get preorder.
//Now we are writing the stack method.

//4-((3+4)-5*2)
//因为想要操作符在数字前输出。。。所以从右到做扫描。。。。
bool isNumbber(char i){
    return i >= '0' && i <= '9';
}

bool isOperator(char i){
    return i == '+' || i == '-' || i == '*' || i == '/';
}

void buildPreByStack(string& input){
    stack<char> num;
    vector<char> res;
    for(int i = input.length() - 1; i >= 0; i--){
        char cur = input[i];
        if(cur == ')'){
            num.push(')');
        }
        if(cur == '('){
            while(!num.empty() && num.top() != ')'){
                res.push_back(num.top());
                num.pop();
            }
            num.pop();
        }
        if(isNumbber(cur)){
            res.push_back(cur);
        }
        if(isOperator(cur)){
            if(cur == '*' || cur == '/'){
                num.push(cur);
            }
            else{
                while(!num.empty() && num.top() != ')' && num.top() != '+' && num.top() != '-'){
                    res.push_back(num.top());
                    num.pop();
                }
                num.push(cur);
            }
        }
    }
    while(!num.empty()){
        res.push_back(num.top());
        num.pop();
    }
    string ans(res.rbegin(), res.rend());
    cout << ans;
}



int main(){
    string input = "1+(2+3)";
    buildPreByStack(input);
}