//
// Created by Ke Ye on 2019-07-20.
//

#include <iostream>

using namespace std;

double squareRoot(int num, int precision){
    int left = 0;
    int right = num;
    double res = 0;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(mid * mid == num){
            res = mid;
            break;
        }
        if(mid * mid < num){
            res = mid;
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    double each = 0.1;
    for(int i = 0; i < precision; i++){
        while(res * res <= num){
            res += each;
        }
        res -= each;
        each /= 10;
    }
    return res;
}

int main() {
    cout << squareRoot(50, 3) << endl;
    cout << squareRoot(10, 4) << endl;
}