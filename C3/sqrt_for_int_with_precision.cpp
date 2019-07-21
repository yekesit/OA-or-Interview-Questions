//
// Created by Ke Ye on 2019-07-20.
//

#include <iostream>
#include <cmath>

using namespace std;

//Also can multiple with precision first, then solve problem all in int....
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

//Then learned from candidate's solution. change input to long and add precision with power of 10.. Nice
double squareRootInt(int num, int precision){
    long n = (long)num * pow(10, precision * 2);
    long left = 0;
    long right = n;
    long res = 0;
    while(left <= right){
        long mid = left + (right - left) / 2;
        cout << mid << endl;
        if(mid * mid == n){
            res = mid;
            break;
        }
        if(mid * mid < n){
            res = mid;
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    double ans = res;
    for(int i = 0; i < precision; i++){
        ans /= 10;
    }
    return ans;

}

int main() {
//    cout << squareRoot(50, 3) << endl;
//    cout << squareRoot(15, 2) << endl;

    cout << squareRootInt(50, 3) << endl;
//    cout << squareRootInt(15, 2) << endl;

}