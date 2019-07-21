//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>

using namespace std;

//Review iteration and recursion
// class Solution{
// public:
//     ListNode* reverseList(ListNode* head) {
//         if(!head || !head->next) return head;

//         ListNode *pre = nullptr;
//         ListNode *cur = head;
//         ListNode *next;
//         while(cur){
//             next = cur->next;
//             cur->next = pre;
//             pre = cur;
//             cur = next;
//         }
//         return pre;
//     }
// };


class Solution{
public:
    ListNode* reverseList(ListNode* head){
        // if(!head || !head->next) return head;
        // ListNode *p = head;
        // head = reverseList(head->next);
        // p->next->next = p;
        // p->next = nullptr;
        // return head;

        if(!head || !head->next) return head;
        ListNode *p = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return p;
    }
};









int main() {

}