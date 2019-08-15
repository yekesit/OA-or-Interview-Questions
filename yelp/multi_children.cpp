#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;


// key value
// des path

// 1 2 3 4 !!
void dfs(unordered_map<char, unordered_set<char>>& next, char cur){
    if(next.find(cur) == next.end()){
        cout << "Destination: " << cur << ' ' << endl;
    }

    for(auto& n : next[cur]){
        dfs(next, n);
    }
}






int main() {
    vector<vector<char>> clicks{
            {'A', 'B'},
            {'B', 'C'},
            {'C', 'D'},
            {'C', 'F'},
            {'D', 'E'},
            {'F', 'G'}
    };

    // shuffle

    unordered_map<char, unordered_set<char>> next;
    // A >> B
    // B >> C
    // C >> D
    // D >> E
    for(auto& c : clicks){
        next[c[0]].insert(c[1]);
    }

    char start;
    cout << "Enter a start!" << endl;
    cin >> start;

    dfs(next, start);


}
