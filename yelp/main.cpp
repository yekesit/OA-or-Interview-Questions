#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;


int main() {
    vector<vector<char>> clicks{
            {'A', 'B'},
            {'B', 'C'},
            {'C', 'D'},
            {'C', 'F'},
            {'D', 'E'},
            {'E', 'A'},
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

    //A B C D !!!
    unordered_set<char> visited{start};

    while(next.find(start) != next.end()){
        start = next[start];
        if(visited.find(start) != visited.end()){
            cout << "Find a cycle here!" << endl;
            break;
        }
        else{
            visited.insert(start);
        }
    }

//    cout << "The destination is: " << start << endl;

}

//