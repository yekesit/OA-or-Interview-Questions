//
// Created by Ke Ye on 2019-06-23.
//

#include <iostream>
#include <vector>
#include <stack>
#include <deque>

using namespace std;

//postorder expression is easy to be built as a tree.
//First use tree

struct Node{
    char val;
    Node *left;
    Node *right;
    Node(char val) : val(val), left(nullptr), right(nullptr){}
};


void inorder(Node* root){
    if(root->left && root->right){
        cout << '(';
        inorder(root->left);
        cout << root->val;
        inorder(root->right);
        cout << ')';
    }
    else{
        cout << root->val;
    }
}

void postorder(Node* root){
    if(root){
        postorder(root->left);
        postorder(root->right);
        cout << root->val;
    }
}


bool isNumber(char i){
    return i >= '0' && i <= '9';
}

Node* buildExpTreeByPost(string& input){
    stack<Node*> num;
    for(char i : input){
        if(isNumber(i)){
            num.push(new Node(i));
        }
        else{
            Node *right = num.top(); num.pop();
            Node *cur = new Node(i);
            Node *left = num.top(); num.pop();
            cur->right = right;
            cur->left = left;
            num.push(cur);
        }
    }
    return num.top();
}

void buildInByTree(string& input){
    Node *root = buildExpTreeByPost(input);
    inorder(root);
    cout << endl;
}

//Since after we change something, char becomes string. so we save string.. Better!!! Nice
void buildInByDeque(string& input){
    stack<string> num;
    for(char i : input){
        if(isNumber(i)){
            num.push(to_string(i - '0'));
        }
        else{
            string right = num.top(); num.pop();
            string left = num.top(); num.pop();
            string cur;
            cur += '(';
            cur += left;
            cur += i;
            cur += right;
            cur += ')';
            num.push(cur);
        }
    }
    cout << num.top();
}



int main(){
    string input = "123+4*+5-";
    buildInByTree(input);
    buildInByDeque(input);
}