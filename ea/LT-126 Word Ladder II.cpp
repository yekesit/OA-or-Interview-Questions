//
// Created by Ke Ye on 2019-06-14.
//

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

//Solution 1
//Basic solution
class Solution {
public:
    struct Node {
        string str;
        vector<Node *> next;

        explicit Node(string &str) : str(str) {}
    };

    void update(vector<vector<string>> &res, Node *root, vector<string> cur, string &endWord) {
        cur.push_back(root->str);

        if (root->str == endWord) {
            res.push_back(cur);
        } else {
            for (int i = 0; i < root->next.size(); i++) {
                update(res, root->next[i], cur, endWord);
            }
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        if (wordList.empty()) return {{}};
        vector<vector<string>> res;
        unordered_set<string> words(wordList.begin(), wordList.end());
        unordered_set<string> exist{beginWord};
        unordered_map<string, Node *> map;
        if (words.find(endWord) == words.end()) return res;
        queue<Node *> bfs;
        Node *root = new Node(beginWord);
        map[beginWord] = root;
        bfs.push(root);
        bool flag = false;
        int length = beginWord.length();
        while (!bfs.empty()) {
            unordered_set<string> cur_level;
            for (int i = bfs.size() - 1; i >= 0; i--) {
                Node *cur = bfs.front();
                bfs.pop();
                for (int j = 0; j < length; j++) {
                    string tmp = cur->str;
                    for (char k = 'a'; k <= 'z'; k++) {
                        if (k == cur->str[j]) continue;
                        tmp[j] = k;
                        //Actually here we can change a little to make it concise
//                        if (tmp == endWord) {
//                            flag = true;
//                            cur->next.push_back(new Node(endWord));
//                        } else {
//                            if (words.find(tmp) != words.end()) {
//                                if (exist.find(tmp) == exist.end()) {
//                                    if (map.find(tmp) == map.end()) {
//                                        Node *next = new Node(tmp);
//                                        map[tmp] = next;
//                                    }
//                                    cur->next.push_back(map[tmp]);
//                                    if (cur_level.find(tmp) == cur_level.end()) {
//                                        bfs.push(map[tmp]);
//                                        cur_level.insert(tmp);
//                                    }
//
//                                }
//                            }
//                        }
                        if (words.find(tmp) != words.end()) {
                            if (exist.find(tmp) == exist.end()) {
                                if (map.find(tmp) == map.end()) {
                                    Node *next = new Node(tmp);
                                    map[tmp] = next;
                                }
                                cur->next.push_back(map[tmp]);
                                if (cur_level.find(tmp) == cur_level.end()) {
                                    bfs.push(map[tmp]);
                                    cur_level.insert(tmp);
                                }
                                if(tmp == endWord){
                                    flag = true;
                                }
                            }
                        }

                    }
                }
            }
            exist.insert(cur_level.begin(), cur_level.end());
            if (flag) break;
        }
        update(res, root, {}, endWord);
        return res;
    }
};

//save path in queue.
//easy to remember. slower than first solution.
class Solution1 {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        if (wordList.empty()) return {};
        unordered_set<string> words(wordList.begin(), wordList.end());
        if (words.find(endWord) == words.end()) return {};
        queue<vector<string>> bfs;
        bfs.push(vector<string>{beginWord});
        bool flag = false;
        int length = beginWord.length();
        vector<vector<string>> res;
        while (!bfs.empty()) {
            unordered_set<string> cur_level;
            for (int i = bfs.size(); i > 0; i--) {
                vector<string> cur_path = bfs.front();
                bfs.pop();
                string cur_str = cur_path.back();
                for (int j = 0; j < length; j++) {
                    string cur_str_tmp = cur_str;
                    for (int k = 'a'; k <= 'z'; k++) {
                        if (k == cur_str[j]) continue;
                        cur_str_tmp[j] = k;
                        if (words.find(cur_str_tmp) != words.end()) {
                            vector<string> next = cur_path;
                            next.push_back(cur_str_tmp);
                            cur_level.insert(cur_str_tmp);
                            bfs.push(next);
                            if (cur_str_tmp == endWord) {
                                res.push_back(next);
                                flag = true;
                            }
                        }
                    }
                }
            }
            for (auto &c : cur_level) {
                words.erase(c);
            }
            if (flag) break;
        }
        return res;
    }
};


int main() {
    string beginWord = "red";
    string endWord = "tax";
    vector<string> wordList{"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};
    Solution s;
    Solution1 s1;
    vector<vector<string>> res = s.findLadders(beginWord, endWord, wordList);
    for (auto &r : res) {
        for (auto &rr : r) {
            cout << rr << ' ';
        }
        cout << endl;
    }

}
