//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>

using namespace std;

class Solution {
public:
    Node* connect(Node* root) {
        Node *cur = root;
        Node *next_dummy = new Node();
        next_dummy->next = nullptr;
        Node *p = next_dummy;
        while(cur){
            if(cur->left){
                p->next = cur->left;
                p = p->next;
            }
            if(cur->right){
                p->next = cur->right;
                p = p->next;
            }
            if(cur->next){
                cur = cur->next;
            }
            else{
                cur = next_dummy->next;
                next_dummy->next = nullptr;
                p = next_dummy;
            }
        }
        return root;
    }
};

int main() {


}