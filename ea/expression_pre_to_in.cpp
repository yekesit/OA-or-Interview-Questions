//
// Created by Ke Ye on 2019-06-23.
//

#include <iostream>
#include <stack>
using namespace std;

//- + 1 * + 23 4 5
//First build tree then inorder


struct Node{
    char val;
    Node *left;
    Node *right;
    Node(char val) : val(val),left(nullptr), right(nullptr){}
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

void preorder(Node* root){
    if(root){
        cout << root->val;
        preorder(root->left);
        preorder(root->right);
    }
}

bool isNumber(char i){
    return i >= '0' && i <= '9';
}

Node* buildTreeByPre(string& input){
    stack<Node*> num;
    for(int i = input.length() - 1; i >= 0; i--){
        char cur = input[i];
        if(isNumber(cur)){
            num.push(new Node(cur));
        }
        else{
            Node *left = num.top(); num.pop();
            Node *right = num.top(); num.pop();
            Node *ope = new Node(cur);
            ope->right = right;
            ope->left = left;
            num.push(ope);
        }
    }
    return num.top();
}


void buildInByTree(string& input){
    Node *root = buildTreeByPre(input);
    preorder(root);
    cout << endl;
    inorder(root);
    cout << endl;
}


void buildInByStack(string& input){
    stack<string> num;
    for(int i = input.length() - 1; i >= 0; i--){
        char cur = input[i];
        if(isNumber(cur)){
            num.push(to_string(cur - '0'));
        }
        else{
            string left = num.top(); num.pop();
            string right = num.top(); num.pop();
            string tmp;
            tmp += '(';
            tmp += left;
            tmp += cur;
            tmp += right;
            tmp += ')';
            num.push(tmp);
        }
    }
    cout << num.top();
}

int main() {
    string input = "-+1*+2345";
    buildInByTree(input);
    buildInByStack(input);
}