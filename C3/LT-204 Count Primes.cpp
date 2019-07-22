//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>
#include <vector>

using namespace std;

//Generate prime below n
class Solution {
public:
    int countPrimes(int n) {
        if(n <= 2) return 0;
        vector<bool> is_prime(n, true);
        is_prime[0] = is_prime[1] = false;
        for(int i = 2; i < sqrt(n); i++){
            if(is_prime[i]){
                for(int j = i * i; j < n; j += i){
                    is_prime[j] = false;
                }
            }
        }

        return count(is_prime.begin(), is_prime.end(), true);
    }
};



int main() {

}