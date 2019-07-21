//
// Created by Ke Ye on 2019-07-21.
//

#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;


struct Edge{
    char u;
    char v;
    int weight;
    Edge(char u, char v, int weight): u(u), v(v), weight(weight){}
};




class UnionFind{
public:
    UnionFind(){
        parent.resize(26, -1);
        count = 0;
    }

    int Find(int child){
        if(parent[child] == -1){
            count++;
            parent[child] = child;
        }
        return child == parent[child] ? child : parent[child] = Find(parent[child]);
    }

    void Union(int c1, int c2){
        int p1 = Find(c1);
        int p2 = Find(c2);
        if(p1 == p2) return;
        count++; // a new edge.
        cout << (char)(c1 + 'A') << "-------" << (char)(c2 + 'A') << endl;
        parent[p1] = p2;
    }
private:
    vector<int> parent;
    int count;
};


void kruskal_MST(vector<Edge>& edges){
    unordered_set<char> vertex_set; // count numbers
    for(auto& e : edges){
        vertex_set.insert(e.u);
        vertex_set.insert(e.v);
    }
    sort(edges.begin(), edges.end(), [](Edge& e1, Edge& e2){ return e1.weight < e2.weight; });
    UnionFind uf;
    for(auto& e : edges){
        uf.Union(e.u - 'A', e.v - 'A');
    }
}



int main() {
    Edge e1('A', 'B', 6);
    Edge e2('B', 'C', 4);
    Edge e3('C', 'D', 6);
    Edge e4('D', 'E', 8);
    Edge e5('E', 'F', 8);
    Edge e6('B', 'F', 10);
    Edge e7('E', 'C', 5);
    Edge e8('F', 'C', 7);
    Edge e9('B', 'E', 3);
    Edge e10('A', 'F', 1);
    vector<Edge> edges{e1, e2, e3, e4, e5, e6, e7, e8, e9, e10};
    kruskal_MST(edges);
}