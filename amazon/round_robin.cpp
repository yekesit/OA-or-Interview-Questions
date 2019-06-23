//
// Created by Ke Ye on 2019-06-19.
//

#include <iostream>
#include <vector>

using namespace std;

double roundRobin(vector<int>& arrive, vector<int>& excute, int q){
    if(arrive.empty() || excute.empty()) return 0.0;
    vector<pair<int, int>> tasks(arrive.size());
    double sum = 0;
    for(int i = 0; i < arrive.size(); i++){
        tasks[i].first = arrive[i];
        tasks[i].second = excute[i];
    }
    for(auto& t : tasks){
        cout << t. first << ' ' << t.second << endl;
    }
    return sum;
}


int main(){
    vector<int> arrive{0,1,3,9};
    vector<int> excute{2,1,7,5};
    int q = 3;
    cout << roundRobin(arrive, excute, q);
}