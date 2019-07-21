//
// Created by Ke Ye on 2019-07-17.
//

#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <sstream>

using namespace std;


//LT-264 Ugly Number II
class Solution_0{
public:
    int nthUglyNumber(int n) {
        if (!n) return n;
        int id2 = 0, id3 = 0, id5 = 0, rst = 1;
        vector<int> buf;

        while (--n) {
            buf.push_back(rst);

            int v2 = 2 * (buf[id2]), v3 = 3 * (buf[id3]), v5 = 5 * (buf[id5]);
            rst = min(v2, min(v3, v5));

            id2 += (rst == v2), id3 += (rst == v3), id5 += (rst == v5);
        }
        return rst;
    }
};


//LT-4 median of Two Sorted Array
//      left_part          |        right_part
//A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
//B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]

class Solution_1 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.size() > nums2.size()){
            swap(nums1, nums2);
        }
        int l1 = nums1.size();
        int l2 = nums2.size();
        int iMin = 0;
        int iMax = l1;
        int half_len = (l1 + l2 + 1) / 2;
        while(iMin <= iMax){
            int i = (iMin + iMax) / 2;
            int j = half_len - i;
            //i is too small
            if(i < iMax && nums2[j - 1] > nums1[i]){
                iMin++;
            }
                //i is too large
            else if(i > iMin && nums1[i - 1] > nums2[j]){
                iMax--;
            }
            else{
                int max_left = 0;
                if(i == 0) {
                    max_left = nums2[j - 1];
                }
                else if(j == 0) {
                    max_left = nums1[i - 1];
                }
                else{
                    max_left = max(nums1[i - 1], nums2[j - 1]);
                }
                //Since we use half_len = (l1 + l2 + 1) / 2. And the value of half_len is the number of left_part
                //So in this case, we promiss len(left) >= len(right) (same or plus one).
                //So when we get max_left, and the length is odd. we get the median.
                //Same for there is no + 1 here. right part is longer.
                if((l1 + l2) % 2 == 1 ) return max_left;
                int max_right = 0;
                if(i == l1){
                    max_right = nums2[j];
                }
                else if(j == l2){
                    max_right = nums1[i];
                }
                else{
                    max_right = min(nums1[i], nums2[j]);
                }
                return (max_left + max_right) / 2.0;

            }
        }
        return 0.0;
    }
};

//LT-772  Basic Calculator III
class Solution_2 {
public:
    int calculate(string s) {
        if(s.empty()) return 0;
        stack<long> nums;
        stack<char> opes;
        int len = s.length();
        int i = 0;
        long num1 = 0;
        long num2 = 0;
        char ope;
        char pre = '+';
        int sign = 1;
        while(i < len){
            if(s[i] == ' '){
                //do nothing
            }
            else if(s[i] == '('){
                opes.push(s[i]);
                pre = '(';
            }
            else if(s[i] == ')'){
                while(opes.top() != '('){
                    num2 = nums.top(); nums.pop();
                    num1 = nums.top(); nums.pop();
                    ope = opes.top(); opes.pop();
                    nums.push(calculate(num1, num2, ope));
                }
                opes.pop(); // '('
            }
            else if(pri.find(s[i]) != pri.end()){
                if(pri.find(pre) != pri.end()){
                    sign = s[i] == '-' ? -1 : 1;
                }
                else{
                    while(!opes.empty() && pri[opes.top()] >= pri[s[i]]){
                        num2 = nums.top(); nums.pop();
                        num1 = nums.top(); nums.pop();
                        ope = opes.top(); opes.pop();
                        nums.push(calculate(num1, num2, ope));
                    }
                    opes.push(s[i]);
                }
            }
            else{
                int j = i;
                while(j < len && isdigit(s[j])){
                    j++;
                }
                nums.push(stol(s.substr(i, j - i)) * sign);
                i = j - 1;
                pre = '0';
                sign = 1;
            }
            i++;
        }
        while(!opes.empty()){
            num2 = nums.top(); nums.pop();
            num1 = nums.top(); nums.pop();
            ope = opes.top(); opes.pop();
            nums.push(calculate(num1, num2, ope));
        }
        return nums.top();

    }
private:
    unordered_map<char, int> pri{
            {'(', 0},
            {'+', 2},
            {'-', 2},
            {'*', 3},
            {'/', 3}
    };
    long calculate(long num1, long num2, char ope){
        switch(ope){
            case '+': return num1 + num2;
            case '-': return num1 - num2;
            case '*': return num1 * num2;
            case '/': return num1 / num2;
        }
        return 0;
    }
};

//LT-42 Trapping water
class Solution_3 {
public:
    int trap(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int cur_level = 0;
        int water = 0;
        while(left < right){
            if(height[left] < height[right]){
                cur_level = max(height[left], cur_level);
                water += cur_level - height[left];
                left++;
            }
            else{
                cur_level = max(height[right], cur_level);
                water += cur_level - height[right];
                right--;
            }
        }
        return water;
    }
};

//LT-68 Text Justification
class Solution_4 {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int cur_length = 0;
        int cur_str_len = 0;
        int cur_count = 0;
        int left = 0;
        int right = 0;
        int size = words.size();
        vector<string> ans;
        while(left < size){
            while(right < size && cur_length + words[right].length() <= maxWidth){
                cur_length += words[right].length() + 1;
                cur_str_len += words[right].length();
                cur_count++;
                right++;
            }
            cur_count--; // 4 people has 3 intervals
            //If meet the final line
            if(right == size){
                string res(maxWidth, ' ');
                int index = 0;
                while(left < right){
                    for(int i = 0; i < words[left].length(); i++, index++){
                        res[index] = words[left][i];
                    }
                    index++;
                    left++;
                }
                ans.push_back(res);
            }
                //If not the final line.
            else{
                int space = maxWidth - cur_str_len;
                string res(maxWidth, ' ');
                int index = 0;
                while(left < right){
                    for(int i = 0; i < words[left].length(); i++, index++){
                        res[index] = words[left][i];
                    }
                    left++;
                    if(!cur_count) break;
                    int interval = space / cur_count;
                    if(space % cur_count != 0) interval++;
                    cur_count--;
                    index += interval;
                    space -= interval;

                }
                ans.push_back(res);
            }
            cur_length = 0;
            cur_count = 0;
            cur_str_len = 0;
        }
        return ans;
    }
};


//LT-418 418. Sentence Screen Fitting
class Solution_5 {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        unordered_map<int, int> cnt_after;
        int num = 0;
        int size = sentence.size();
        for(int i = 0; i < rows; i++){
            int start = num % size;
            if(cnt_after.find(start) == cnt_after.end()){
                int cnt = 0;
                int len = 0;
                for(int j = start; len < cols; j = (j + 1) % size, cnt++){
                    if(len + sentence[j].length() > cols) break;
                    len += sentence[j].length() + 1;
                }
                num += cnt;
                cnt_after[start] = cnt;
            }
            else{
                num += cnt_after[start];
            }
        }
        return num / size;
    }
};

//LT-304. Range Sum Query 2D - Immutable
class NumMatrix {
public:
    vector<vector<int>> partial;
    NumMatrix(vector<vector<int>>& matrix){
        if(matrix.empty()) return;
        int row = matrix.size() + 1;
        int col = matrix[0].size() + 1;
        for(int i = 0; i < row; i++)
            partial.push_back(vector<int>(col, 0));
        for(int i = 1; i < row; i++){
            for(int j = 1; j < col; j++){
                partial[i][j] = partial[i - 1][j] + partial[i][j - 1] - partial[i - 1][j - 1] + matrix[i - 1][j - 1];
                cout << partial[i][j] << ' ';
            }
            cout << endl;
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return partial[row2 + 1][col2 + 1] - partial[row1][col2 + 1] - partial[row2 + 1][col1] + partial[row1][col1];
    }
};

//Website, fill a string into fixed width

//Input: String "John is planning to move to Seattle after getting a new job there.", int maxLimit 20
//Output: String[]
//John is planning to
//move to Seattle
//after getting a new
//job there.
class Solution_6{
public:
    vector<string> fillInFixedWidth(string& input, int width){
        istringstream s(input);
        vector<string> str;
        string tmp;
        while(s >> tmp){
            str.push_back(tmp);
        }

        vector<string> res;
        int i = 0;
        int j = 0;
        int size = str.size();
        while(i < size){
            int len = 0;
            while(j < size && len + str[j].length() <= width){
                len += str[j].length() + 1;
                j++;
            }
            string cur(width, ' ');
            int cur_len = 0;
            while(i < j){
                cur.replace(cur_len, str[i].length(), str[i]);
                cur_len += str[i].length() + 1;
                i++;
            }
            res.push_back(cur);
        }
        return res;

    }
};

//Website, fill a string into fixed width. Can be split if too long.

class Solution_7{
public:
    vector<string> fillInFixedWidth(string& input, int width) {
        vector<string> res;
        istringstream str(input);
        string cur;
        str >> cur;
        while(!cur.empty()){
            string next(width, ' ');
            int len = 0;
            while(len < width){
                if(len + cur.length() > width){
                    string part = cur.substr(0, width - len);
                    cur = cur.substr(width - len);
                    next.replace(len, part.length(), part);
                    len += part.length() + 1;
                }
                else{
                    next.replace(len, cur.length(), cur);
                    len += cur.length() + 1;
                    if(str.eof()) {
                        cur = "";
                        break;
                    }
                    else{
                        str >> cur;
                    }
                }
            }
            res.push_back(next);
        }
        return res;
    }
};


//LT-212 word search II

static const auto x=[](){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

// from word search 1, slow
// class Solution {
// public:
//     bool dfs(vector<vector<char>>& board, int i, int j, int index, string& word){
//         if(index == word.length()) return true;
//         if(i < 0 || j < 0 || i == board.size() || j == board[0].size()) return false;
//         char cur = board[i][j];
//         char check = word[index];
//         if(cur != check) return false;
//         board[i][j] = '0';
//         bool res = dfs(board, i - 1, j, index + 1, word) ||
//                    dfs(board, i + 1, j, index + 1, word) ||
//                    dfs(board, i, j - 1, index + 1, word) ||
//                    dfs(board, i, j + 1, index + 1, word);
//         board[i][j] = cur;
//         return res;
//     }

//     vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
//         set<string> res_set;
//         int row = board.size();
//         int col = board[0].size();
//         for(auto w : words){
//             for(int i = 0; i < row; i++){
//                 for(int j = 0; j < col; j++){
//                     if(dfs(board, i, j, 0, w)) {
//                         res_set.insert(w);
//                     }
//                 }
//             }
//         }
//         vector<string> res(res_set.begin(), res_set.end());
//         return res;
//     }
// };

//Why we use Trie tree??
//https://leetcode.com/problems/word-search-ii/discuss/59780/Java-15ms-Easiest-Solution-(100.00)
//Don't konw how to cur....emmmmmmm
class Solution_8 {
public:
    struct TrieNode{
        TrieNode* next[26];
        string word;
        TrieNode() : word(""){
            for(int i = 0; i < 26; i++){
                next[i] = nullptr;
            }
        }
    };

    TrieNode* buildTrie(vector<string>& words){
        TrieNode *root = new TrieNode();
        for(auto& w : words){
            TrieNode* cur = root;
            for(auto& c : w){
                int index = c - 'a';
                if(cur->next[index] == nullptr){
                    cur->next[index] = new TrieNode();
                }
                cur = cur->next[index];
            }
            cur->word = w;
        }
        return root;
    }

    void dfs(vector<vector<char>>& board, int i, int j, TrieNode* root, vector<string>& res){
        char cur = board[i][j];
        if(cur == '0' || root->next[cur - 'a'] == nullptr) return;
        root = root->next[cur - 'a'];
        if(root->word != ""){
            res.push_back(root->word);
            root->word = "";
        }
        board[i][j] = '0';
        if(i > 0) dfs(board, i - 1, j, root, res);
        if(j > 0) dfs(board, i, j - 1, root, res);
        if(i < board.size() - 1) dfs(board, i + 1, j, root, res);
        if(j < board[0].size() - 1) dfs(board, i, j + 1, root, res);
        board[i][j] = cur;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        TrieNode *root = buildTrie(words);
        vector<string> res;
        for(int i = 0; i < board.size(); i++){
            for(int j = 0; j < board[0].size(); j++){
                dfs(board, i, j, root, res);
            }
        }
        return res;
    }
};


//LT-505 Maze II
//bfs
//Note: Since here we may move many steps in each direction, which means we are not step by step.
//So this is different from step by step bfs. We should check every points even it is already visited.
//Since we may use less steps to get this points in other ways.
//Difference from general bfs and this bfs. Emmmmmmm

//So in this question, bfs dfs both work.
//for dfs, same with The Maze I and the if condition is the same with bfs...... update if small, then continue going next..
class Solution_9 {
public:
    vector<vector<int>> directs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        //Since we can't make unordered_map like this....
        // unordered_map<pair<int, int>, Node*> dis;
        //We make a whole copy of maze to replace this hash map.....emmmm more space;
        vector<vector<int>> dis(maze.size(), vector<int>(maze[0].size(), INT_MAX));
        dis[start[0]][start[1]] = 0;
        pair<int, int> sp(start[0], start[1]);
        queue<pair<int, int>> bfs;
        bfs.push(sp);
        while(!bfs.empty()){
            pair<int, int> cur = bfs.front(); bfs.pop();
            for(auto& d : directs){
                int next_i = cur.first;
                int next_j = cur.second;
                int next_steps = dis[cur.first][cur.second];
                while(next_i >= 0 && next_j >=0 && next_i < maze.size() && next_j < maze[0].size()){
                    if(maze[next_i][next_j] == 1){
                        break;
                    }
                    else{
                        next_i += d[0];
                        next_j += d[1];
                        next_steps++;
                    }
                }
                next_i -= d[0];
                next_j -= d[1];
                next_steps--;
                if(dis[next_i][next_j] > next_steps){
                    dis[next_i][next_j] = next_steps;
                    bfs.push(make_pair(next_i, next_j));
                }
            }
        }
        return dis[destination[0]][destination[1]] == INT_MAX? -1 : dis[destination[0]][destination[1]];
    }
};

//LT-332 Reconstruct Itinerary

//从起始点出发，一直延小的走下去，如果能走完，意味着这条路是对的。如果走不完，意味着我们要先从其他地方走，最后再走到这里
//核心问题在于，这条路根据题意，是一定能走完的，数据是ok的。所以只要遇到这条走不完的路，那就意味着我们不可能先走这部分。
//就一定要先走另外一部分。那么这部分就放在最后走，也就是上面说的一个一个push_back，最后整个转回来就行了。
//主要是充分利用了题目说的这个行程一定是走得完的，也就是这个有向图一定是可以从JFK出发走成功的。。。
//所以才每次可以从最小的走，反正只要走不完就放最后走就行。。。反正能走完。。23333

class Solution_10 {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets){
        if(tickets.empty()) return {};
        unordered_map<string, multiset<string>> go;
        for(auto& t : tickets){
            go[t[0]].insert(t[1]);
        }

        vector<string> res;
        helper(go, "JFK", res);
        reverse(res.begin(), res.end());
        return res;
    }

    void helper(unordered_map<string, multiset<string>>& go, const string& cur, vector<string>& res){
        while(!go[cur].empty()){
            auto small = go[cur].begin();
            string tmp = *small;
            go[cur].erase(small);
            helper(go, tmp, res);
        }
        res.push_back(cur);
    }
};



//LT-72 edit distance
class Solution_11 {
public:
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        int edit_dis[m + 1][n + 1];
        int cost;
        for(int i = 0; i <= m; i++)
            edit_dis[i][0] = i;
        for(int j = 0; j <= n; j++)
            edit_dis[0][j] = j;
        for(int i = 1; i <=m; i++)
            for(int j = 1; j <=n; j++){
                if(word1[i - 1] == word2[j - 1])
                    cost = 0;
                else
                    cost = 1;
                edit_dis[i][j] = min(min(edit_dis[i - 1][j] + 1, edit_dis[i][j - 1] + 1), edit_dis[i - 1][j - 1] + cost);
            }
        return edit_dis[m][n];
    }
};

//LT-244 shortest word distance II
class WordDistance {
public:
    WordDistance(vector<string>& words) {
        for(int i=0;i<words.size();i++)
            wordMap[words[i]].push_back(i);
    }
    int shortest(string word1, string word2) {
        int  i=0, j=0, dist = INT_MAX;
        while(i < wordMap[word1].size() && j <wordMap[word2].size()) {
            dist = min(dist, abs(wordMap[word1][i] - wordMap[word2][j]));
            wordMap[word1][i]<wordMap[word2][j]?i++:j++;
        }
        return dist;
    }
private:
    unordered_map<string, vector<int>> wordMap;
};

//LT-245 Word distance III
class Solution_12 {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        int res = words.size(), l = -1, r = -1;
        for (unsigned int i=0; i<words.size(); i++) {
            if (words[i] == word1)
                l = (word1==word2)?r:i;
            if (words[i] == word2)
                r = i;
            if(l >= 0 && r >= 0)
                res = min(res, abs(l - r));
        }
        return res;
    }
};

int main() {
    Solution_7 s;
    string input = "Hey Joey, your uber is abcdefghijklmnopqrstuvwxyz soon!asdfga";
    int width = 10;
    vector<string> res = s.fillInFixedWidth(input, width);
    for(auto& r : res)
        cout << r << endl;

}