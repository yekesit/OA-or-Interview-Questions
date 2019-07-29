//
// Created by Ke Ye on 2019-07-28.
//

#include <iostream>
#include <stack>
#include <deque>
#include <queue>

using namespace std;


/* Basic thought, use two MinStacks to implement MinQueue
 * Like what we do for implementing queue with two stacks
 * */



class MinQueue1{
public:
    stack<pair<int, int>> s1, s2;
    void enqueue(int x){
        s1.push(make_pair(x, s1.empty() ? x : min(s1.top().second, x)));
    }

    void dequeue() {
        if(s2.empty()){
            while(!s1.empty()){
                auto cur = s1.top(); s1.pop();
                cur.second = s2.empty() ? cur.first : min(s2.top().second, cur.first);
                s2.push(cur);
            }
        }
        s2.pop();
    }

    int findMin() {
        if(s1.empty()) return s2.top().second;
        if(s2.empty()) return s1.top().second;
        return min(s1.top().second, s2.top().second);
    }
};


/* Or we can use same thought with MinStack, use two queues, one for normal number, one for keeping minimum.
 * */

class MinQueue2{
public:
    queue<int> Q;
    deque<int> D;
    void enqueue(int x){
        Q.push(x);
        while(!D.empty() && D.back() > x){
            D.pop_back();
        }
        D.push_back(x);
    }

    void dequeue() {
        if(Q.front() == D.front()){
            D.pop_front();
        }
        Q.pop();

    }

    int findMin() {
        return D.front();
    }
};




int main() {
    MinQueue1 q1;
    MinQueue2 q2;

    q1.enqueue(2);
    q2.enqueue(2);
    q1.enqueue(5);
    q2.enqueue(5);
    cout << q1.findMin() << endl;
    cout << q2.findMin() << endl;
    q1.dequeue();
    q2.dequeue();
    cout << q1.findMin() << endl;
    cout << q2.findMin() << endl;
}