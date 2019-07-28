//
// Created by Ke Ye on 2019-07-27.
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

pair<int, int> isSame(string& s1, string& s2){
    int idx1 = s1.find_last_of(' ');
    int idx2 = s2.find_first_of(' ');
    return s1.substr(idx1 + 1) == s2.substr(0, idx2) ? make_pair(idx1, idx2) : make_pair(-1, -1);
}

vector<vector<string>> mergeTime(vector<vector<string>>& input){
    vector<vector<string>> res{input[0]};
    for(int i = 1; i < input.size(); i++){
        if(res.back()[0] == input[i][0]){
            auto cur = isSame(res.back()[1], input[i][1]);
            if(cur.first > 0){
                res.back()[1] = res.back()[1].substr(0, cur.first) + input[i][1].substr(cur.second + 2);
            }
            else{
                res.push_back(input[i]);
            }
        }
        else{
            res.push_back(input[i]);
        }
    }
    return res;
}

int main() {
    vector<vector<string>> input{
        {"Monday","10:00am - 2:00pm"},
        {"Monday","2:00pm - 6:00pm"},
        {"Tuesday","10:00am - 3:00pm"},
        {"Tuesday","4:00pm - 6:00pm"}
    };


    vector<vector<string>> res = mergeTime(input);
    for(auto& r : res)
        cout << r[0] << ' ' << r[1] << endl;

}