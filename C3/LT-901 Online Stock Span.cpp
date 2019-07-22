//
// Created by Ke Ye on 2019-07-22.
//
#include <iostream>
#include <stack>

using namespace std;

class StockSpanner {
public:
    StockSpanner() {

    }

    int next(int price) {
        int count = 1;
        while(!keep.empty() && price >= keep.top().first ){
            count += keep.top().second; keep.pop();
        }
        keep.push({price, count});
        return count;
    }

private:
    stack<pair<int, int>> keep;
};

int main() {

}