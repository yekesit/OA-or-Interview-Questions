//
// Created by Ke Ye on 2019-06-14.
//

#include <iostream>

using namespace std;

/*
 *  1.basic according to length
    2.X + Z + Y = Y + Z + X. Where
    X is belong to list 1
    Y is belong to list 2
    Z is common list
    So go around two times, then if there is an intersection. We will meet
 */


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */


struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr){}
};

//basic, get length and go from the difference nodes.
// class Solution {
// public:
//     ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
//         int len1 = 0;
//         int len2 = 0;
//         ListNode *p1 = headA;
//         ListNode *p2 = headB;
//         while(p1){
//             len1++;
//             p1 = p1->next;
//         }
//         while(p2){
//             len2++;
//             p2 = p2->next;
//         }
//         p1 = headA;
//         p2 = headB;
//         while(len1 > len2){
//             p1 = p1->next;
//             len1--;
//         }
//         while(len2 > len1){
//             p2 = p2->next;
//             len2--;
//         }
//         while(p1 && p2){
//             if(p1 == p2)
//                 return p1;
//             p1 = p1->next;
//             p2 = p2->next;
//         }
//         return nullptr;
//     }
// };

//Another clever solution. See from internet. faster and save space (O(1) space)
class Solution{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB){
        ListNode *p1 = headA;
        ListNode *p2 = headB;
        bool flag1 = false;
        bool flag2 = false;
        while(p1 && p2){
            if(p1 == p2) return p1;

            if(p1->next == nullptr){
                if(flag1) break;
                p1 = headB;
                flag1 = true;
            }
            else{
                p1 = p1->next;
            }
            if(p2->next == nullptr){
                if(flag2) break;
                p2 = headA;
                flag2 = true;
            }
            else{
                p2 = p2->next;
            }
        }
        return nullptr;
    }
};


int main(){

}