#include <iostream>
#include <stack>

using namespace std;

struct Node{
    char val;
    Node *left;
    Node *right;
    Node(char val) : val(val), left(nullptr), right(nullptr){}
};


void inorder(Node* root){
    if(root){
        inorder(root->left);
        cout << root->val;
        inorder(root->right);
    }
}

void postorder(Node* root){
    if(root){
        postorder(root->left);
        postorder(root->right);
        cout << root->val;
    }
}


//transform expression to binary tree then postorder get result
// 8 - (3 + 5) * (5 - 6 / 2)
bool isNumbber(char i){
    return i >= '0' && i <= '9';
}
bool isOperator(char i){
    return i == '+' || i == '-' || i == '*' || i == '/';
}
Node* buildExpTreeByIn(string& input){
    stack<Node*> num;
    stack<char> ope;
    for(char i : input){
        if(i == '('){
            ope.push(i);
        }
        if(i == ')'){
            while(ope.top() != '(') {
                Node *right = num.top();
                num.pop();
                Node *cur = new Node(ope.top());
                ope.pop();
                Node *left = num.top();
                num.pop();
                cur->left = left;
                cur->right = right;
                num.push(cur);
            }
            ope.pop();
        }
        if(isNumbber(i)){
            Node *new_num = new Node(i);
            num.push(new_num);
        }
        if(isOperator(i)){
            if(i == '*' || i == '/'){
                ope.push(i);
            }
            if(i == '+' || i == '-'){
                if(ope.empty() || ope.top() == '('){
                    ope.push(i);
                }
                else{
                    //Since '+' and '-' has lowest priority, so all operators before them should be built first.
                    //Until it is empty or we meet (
                    while(!ope.empty() && ope.top() != '(') {
                        Node *right = num.top();
                        num.pop();
                        Node *pre = new Node(ope.top());
                        ope.pop();
                        Node *left = num.top();
                        num.pop();
                        pre->right = right;
                        pre->left = left;
                        num.push(pre);
                    }
                    ope.push(i);
                }
            }
        }
    }
    while(!ope.empty()){
        Node *right = num.top(); num.pop();
        Node *pre = new Node(ope.top()); ope.pop();
        Node *left = num.top(); num.pop();
        pre->right = right;
        pre->left = left;
        num.push(pre);
    }
    return num.top();
}

void buildPostExpByTree(string& input){
    Node *root = buildExpTreeByIn(input);
    postorder(root);
    cout << endl;
}


void buildPostExpByStack(string& input){
    stack<char> ope;
    for(char i : input){
        if(i == '('){
            ope.push(i);
        }
        if(i == ')'){
            while(ope.top() != '('){
                cout << ope.top();
                ope.pop();
            }
            ope.pop();
        }
        if(isNumbber(i)){
            cout << i;
        }
        if(isOperator(i)){
            if(i == '*' || i == '/'){
                ope.push(i);
            }
            else{
                if(ope.empty() || ope.top() == '('){
                    ope.push(i);
                }
                else{
                    while(!ope.empty() && ope.top() != '('){
                        cout << ope.top();
                        ope.pop();
                    }
                    ope.pop();
                }
            }
        }
    }
    while(!ope.empty()){
        cout << ope.top(); ope.pop();
    }
}



int main() {
    string input = "4-((3+4)-4/5*2)";
    buildPostExpByTree(input);
    buildPostExpByStack(input);
}