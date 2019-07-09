//
// Created by Ke Ye on 2019-07-07.
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
#include <sstream>
#include <stack>

using namespace std;

//Square for sorted array
class Solution_1 {
public:
    vector<int> sortedSquares(vector<int> &A) {
        int left = 0;
        int right = A.size() - 1;
        int idx = right;
        vector<int> res(right + 1);
        while (left <= right) {
            if (A[left] + A[right] >= 0) {
                res[idx--] = A[right] * A[right];
                right--;
            } else {
                res[idx--] = A[left] * A[left];
                left++;
            }
        }
        return res;
    }
};

//Smallest window range


class Solution_2 {
public:
    vector<int> smallestRange(vector<vector<int>> &nums) {
        priority_queue<Node *, vector<Node *>, cmp> que;
        int cur_max = INT_MIN;
        for (int i = 0; i < nums.size(); i++) {
            que.push(new Node(nums[i][0], i, 0, nums[i].size()));
            cur_max = max(cur_max, nums[i][0]);
        }
        int cur_min = que.top()->val;
        vector<int> res{cur_min, cur_max};
        while (!que.empty()) {
            Node *cur = que.top();
            que.pop();
            if (cur->c < cur->size - 1) {
                cur->c++;
                cur->val = nums[cur->r][cur->c];
                que.push(cur);
                cur_max = max(cur_max, cur->val);
                cur_min = que.top()->val;
                if (cur_max - cur_min < res[1] - res[0]) {
                    res[1] = cur_max;
                    res[0] = cur_min;
                }
            } else {
                return res;
            }
        }
        return res;
    }

private:
    struct Node {
        int val;
        int r, c;
        int size;

        Node(int val, int r, int c, int size) : val(val), r(r), c(c), size(size) {}
    };

    struct cmp {
        bool operator()(Node *n1, Node *n2) {
            return n1->val > n2->val;
        }
    };
};


//FizzBuzz
class Solution_3 {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> res;
        for (int i = 1; i <= n; i++) {
            string cur;
            if (i % 3 == 0) {
                cur += "Fizz";
            }
            if (i % 5 == 0) {
                cur += "Buzz";
            }
            if (cur.empty()) {
                cur = to_string(i);
            }
            res.push_back(cur);
        }
        return res;
    }
};


//Remove given character from string
class Solution_4 {
public:
    string removeCharacter(string &&s, char target) {
        int len = 0;
        for (char &c : s) {
            if (c != target) {
                s[len++] = c;
            }
        }
        return s.substr(0, len);
    }
};


//Word ladder II

class Solution_5 {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
        if (wordList.empty()) return {};
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (dict.find(endWord) == dict.end()) return {};
        dict.erase(beginWord);
        dict.erase(endWord);
        unordered_map<string, vector<string>> children;
        vector<vector<string>> res;
        vector<string> path{beginWord};
        buildTree(beginWord, endWord, dict, children);
        buildPath(beginWord, endWord, res, children, path);
        return res;
    }

private:
    bool buildTree(string &beginWord, string &endWord,
                   unordered_set<string> &dict,
                   unordered_map<string, vector<string>> &children) {
        unordered_set<string> begin{beginWord};
        unordered_set<string> end{endWord};
        int len = beginWord.length();
        bool found = false;
        bool fromhead = true;
        while (!begin.empty() && !end.empty()) {
            if (begin.size() > end.size()) {
                swap(begin, end);
                fromhead = !fromhead;
            }
            unordered_set<string> cur_level;
            for (auto &str : begin) {
                for (int i = 0; i < len; i++) {
                    string tmp = str;
                    for (char j = 'a'; j <= 'z'; j++) {
                        tmp[i] = j;
                        if (end.find(tmp) != end.end()) {
                            fromhead ? children[str].push_back(tmp) : children[tmp].push_back(str);
                            found = true;
                        } else if (dict.find(tmp) != dict.end()) {
                            fromhead ? children[str].push_back(tmp) : children[tmp].push_back(str);
                            cur_level.insert(tmp);
                        }
                    }
                }
            }
            if (found) return true;
            for (auto &c : cur_level) {
                dict.erase(c);
            }
            begin = cur_level;
        }
        return false;
    }


    void buildPath(string &beginWord, string &endWord,
                   vector<vector<string>> &res,
                   unordered_map<string, vector<string>> &children,
                   vector<string> &path) {
        if (beginWord == endWord) {
            res.push_back(path);
            return;
        }
        for (auto &c : children[beginWord]) {
            path.push_back(c);
            buildPath(c, endWord, res, children, path);
            path.pop_back();
        }

    }
};


//Intersection of two linked Lists
//Assume two given lists can not have an intersection.
class Solution_6 {
public:
    struct ListNode {
        int val;
        ListNode *next;

        explicit ListNode(int val) : val(val), next(nullptr) {}
    };

    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *p1 = headA;
        ListNode *p2 = headB;
        bool p1_null = false;
        bool p2_null = false;
        while (p1 && p2) {
            if (p1 == p2) return p1;
            if (!p1->next) {
                if (p1_null) break;
                p1 = headB;
                p1_null = true;
            } else {
                p1 = p1->next;
            }

            if (!p2->next) {
                if (p2_null) break;
                p2 = headA;
                p2_null = true;
            } else {
                p2 = p2->next;
            }
        }
        return nullptr;
    }

};

//strstr >> use kmp here
class Solution_7 {
public:
    int strStr(string &s, string &t) {
        if (t.empty()) return 0;
        int len_s = s.length();
        int len_t = t.length();
        vector<int> next(len_t, -1);
        int i = 0;
        int j = -1;
        while (i < len_t - 1) {
            if (j == -1 || t[i] == t[j]) {
                i++;
                j++;
                next[i] = j;
            } else {
                j = next[j];
            }
        }
        i = 0;
        j = 0;
        while (i < len_s) {
            if (j == -1 || s[i] == t[j]) {
                i++;
                j++;
                if (j == len_t) return i - len_t;
            } else {
                j = next[j];
            }
        }
        return -1;
    }
};

//strstr try boyer-moore
//https://www.cnblogs.com/ECJTUACM-873284962/p/7637875.html
//Emmm learn about it.. for 1 and half an hour.... Finally got what should I write..
//But only a basic knowledge.. not very familiar..
class Solution_8 {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        int len_h = haystack.length();
        int len_n = needle.length();
        vector<int> bmBC(256, len_n);
        vector<int> bmGS(len_n, len_n);
        buildBmBC(bmBC, needle, len_n);
        buildBmGS(bmGS, needle, len_n);

        int j = 0;
        int i = 0;
        while (j <= len_h - len_n) {
            for (i = len_n - 1; i >= 0 && needle[i] == haystack[i + j]; i--);
            if (i < 0) {
                return j;
            } else {
                j += max(bmBC[haystack[i + j]] - (len_n - 1 - i), bmGS[i]);
            }
        }
        return -1;

    }

private:
    void buildBmBC(vector<int> &bmBC, string &needle, int &len_n) {
        for (int i = 0; i < len_n - 1; i++) {
            bmBC[needle[i]] = len_n - 1 - i; // the length from the charcter to end
            // for future compared with the current length to get final move steps.
        }
    }

    void suffix(vector<int> &suff, string &needle, int &len_n) {
        suff.resize(len_n, len_n);
        int f = 0;
        int g = len_n - 1;
        for (int i = len_n - 2; i >= 0; i--) {
            if (i > g && suff[len_n - 1 - (f - i)] < i - g) {
                suff[i] = suff[len_n - 1 - (f - i)];
            } else {
                g = min(g, i); //next start
                f = i;         //current head
                while (g >= 0 && needle[g] == needle[len_n - 1 - (f - g)]) g--;
                suff[i] = f - g;
            }
        }
    }

    void buildBmGS(vector<int> &bmGS, string &needle, int &len_n) {
        vector<int> suff;
        suffix(suff, needle, len_n);
        int j = 0;
        for (int i = len_n - 1; i >= 0; i--) {
            if (suff[i] == i + 1) {
                for (; j <= len_n - 1 - (i + 1); j++) {
                    if (bmGS[j] == len_n) {
                        bmGS[j] = len_n - 1 - i;
                    }
                }
            }
        }
        for (int i = 0; i <= len_n - 2; i++) {
            bmGS[len_n - 1 - suff[i]] = len_n - 1 - i;
        }
    }
};


//Missing number >> fixed length n >> with a miss number between 0 and n
class Solution_9 {
public:
    int missingNumber(vector<int> &nums) {
        if (nums.empty()) return 0;
        int sum = 0;
        int size = nums.size();
        for (auto &n : nums) {
            sum += n;
        }
        return (1 + size) * size / 2 - sum;
    }
};

//Find first missing positive number
class Solution_10 {
public:
    int firstMissingPositive(vector<int> &nums) {
        int i = 0;
        int size = nums.size();
        while (i < size) {
            if (nums[i] <= 0 || nums[i] > size || nums[i] == i + 1 || nums[nums[i] - 1] == nums[i]) {
                i++;
            } else {
                swap(nums[nums[i] - 1], nums[i]);
            }
        }
        for (int i = 0; i < size; i++) {
            if (nums[i] != i + 1) return i + 1;
        }
        return size + 1;
    }
};


//Set Matrix Zeroes
class Solution_11 {
public:
    void setZeroes(vector<vector<int>> &matrix) {
        int row = matrix.size();
        int col = matrix[0].size();
        bool row_0 = false;
        bool col_0 = false;
        for (int i = 0; i < col; i++) {
            if (!matrix[0][i]) {
                row_0 = true;
                break;
            }
        }
        for (int i = 0; i < row; i++) {
            if (!matrix[i][0]) {
                col_0 = true;
                break;
            }
        }

        for (int i = 1; i < row; i++)
            for (int j = 1; j < col; j++) {
                if (!matrix[i][j]) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        for (int i = 1; i < row; i++)
            for (int j = 1; j < col; j++) {
                if (!matrix[i][0] || !matrix[0][j])
                    matrix[i][j] = 0;
            }
        if (row_0) {
            for (int i = 0; i < col; i++)
                matrix[0][i] = 0;
        }
        if (col_0) {
            for (int i = 0; i < row; i++)
                matrix[i][0] = 0;
        }
    }
};


//number of island
//Also can be solved by bfs or union find
class Solution_12 {
public:
    int numIslands(vector<vector<char>> &grid) {
        if (grid.empty()) return 0;
        int row = grid.size();
        int col = grid[0].size();
        int island = 0;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++) {
                if (grid[i][j] == '1') {
                    island++;
                    dfs(grid, row, col, i, j);
                }
            }
        return island;
    }

private:
    void dfs(vector<vector<char>> &grid, int row, int col, int i, int j) {
        if (i < 0 || j < 0 || i == row || j == col || grid[i][j] == '0') return;
        grid[i][j] = '0';
        dfs(grid, row, col, i - 1, j);
        dfs(grid, row, col, i + 1, j);
        dfs(grid, row, col, i, j - 1);
        dfs(grid, row, col, i, j + 1);
    }
};

//Maximum subarray sum modulo m
//Return the subarray
class Solution_13 {
public:
    vector<int> maxSubarray(vector<int> &nums, int m) {
        set<pair<int, int>, cmp> prefix;
        int pre_sum = 0;
        int max_mod = INT_MIN;
        int start = 0;
        int end = 0;
        for (int i = 0; i < nums.size(); i++) {
            pre_sum = (pre_sum + nums[i]) % m;
            if (max_mod < pre_sum) {
                max_mod = pre_sum;
                start = 0;
                end = i;
            }
            prefix.insert({pre_sum, i});
            auto it = prefix.upper_bound({pre_sum, i});
            if (it != prefix.end()) {
                int cur = (pre_sum - it->first + m) % m;
                if (cur > max_mod) {
                    max_mod = cur;
                    start = it->second + 1;
                    end = i;
                }
            }
        }
        vector<int> res(nums.begin() + start, nums.begin() + end + 1);
        return res;
    }

private:
    struct cmp {
        bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) const {
            return p1.first < p2.first;
        }
    };
};





//Fibonacci
// Basci two pointes dp
// class Solution {
// public:
//     int climbStairs(int n) {
//         if(n <= 2) return n;
//         int one = 1;
//         int two = 2;
//         for(int i = 3; i <= n; i++){
//             int cur = one + two;
//             one = two;
//             two = cur;
//         }
//         return two;
//     }
// };


//A >> { 1, 1 }
//     { 1, 0 }

//F0 >> { 1, 0 }  >> 1st fibo >> 1
//      { 0, 1 }


//F1 >> {1, 1}   >> 2nd fibo >> 1
//   >> {1, 0}


//F2 >> {2, 1}  >> 3rd fibo >> 2
//      {1, 1}


//so now if we want to get 4th fibo we know that F3 = A * F2 = A^2 * F1 = A^3 * F0;
//and 4 is  1 0 0. to save time, we just keep use ^2 to make it logn
//But in this question, we don't care about 1st fibo... since in this question it begins at 2nd fibo
//So if n == 1 means we need get F1 which is A * F0
//if n == 2 means we need get F2 = A * F1 = A^2 * F0
//if n == 3  >> we get F3 = A* F2 = A * A^2 * F0;
//which means >> we get Fn = A^n * F0
//So we can keep /= 2 >> for example, F5 >> since 5 % 2 == 1 >> we first get A * F0 >> then A >> A ^ 2 >> A ^ 4 >>
//Finally we get A^4 * A * F0 = F5 >> the result
//So if n is the power of 2 >> we can keep make A >> A^2 >> A^4
//But what if n is not the power of 2? Like n = 6
//Then we know 6 = 4 + 2 . And we also can get 6 /2 = 3 >> 3 /2 = 1
//During this time, we get a A^4. but since there are 3 and 1 which can not be divided by 2. So we should add A here.
//So finally, if current n mod 2 == 0 we just multiply A
//if not, means we miss an A here, we multiply it


//Binets Method..... emmmm matrix.
//Don't understand, lol. Remember.
// class Solution{
// public:
//     int climbStairs(int n) {
//         int base[2][2] = {{1, 1}, {1, 0}};
//         int res[2][2] = {{1, 0}, {0, 1}};
//         pow(base, res, n);
//         return res[0][0];
//     }

//     void pow(int base[2][2], int res[2][2], int n){
//         while(n > 0){
//             if((n & 1) == 1){
//                 multiply(base, res);
//             }
//             n >>= 1;
//             multiply(base, base);
//         }
//     }

//     void multiply(int base[2][2], int res[2][2]){
//         long long next[2][2];
//         for(int i = 0; i < 2; i++)
//             for(int j = 0; j < 2; j++){
//                 next[i][j] = long(base[i][0]) * long(res[0][j]) + long(base[i][1]) * long(res[1][j]);
//             }
//         for(int i = 0; i < 2; i++)
//             for(int j = 0; j < 2; j++)
//                 res[i][j] = next[i][j];
//     }
// };

//fibonacci formula

class Solution_14 {
public:
    int climbStairs(int n) {
        double sqrt5 = sqrt(5);
        double fibn = pow((1 + sqrt5) / 2, n + 1) - pow((1 - sqrt5) / 2, n + 1);
        return (int) (fibn / sqrt5);
    }
};


//game of life
//If current is 1 and next is 0 >> we make it -1. since it still counts as 1 at this loop
//If current is 0 and next i 1 >> we make if 2, since it still counts as 0 at this loop.
//So when we count neighbors, we should take care of the current status and next status.
class Solution_15 {
public:
    int num(vector<vector<int>> &board, int i, int j) {
        int total = 0;
        for (int p = -1; p <= 1; p++) {
            for (int q = -1; q <= 1; q++) {
                if (p == 0 && q == 0) continue;
                int cur_i = i + p;
                int cur_j = j + q;
                if (cur_i < 0 || cur_i == board.size() || cur_j < 0 || cur_j == board[0].size()) continue;
                if (board[cur_i][cur_j] == 1 || board[cur_i][cur_j] == -1) total++;
            }
        }
        return total;
    }

    void gameOfLife(vector<vector<int>> &board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                int total = num(board, i, j);
                if (board[i][j] == 0) {
                    if (total == 3) board[i][j] = 2;
                }
                if (board[i][j] == 1) {
                    if (total < 2 || total > 3) board[i][j] = -1;
                }
            }
        }
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 2) board[i][j] = 1;
                if (board[i][j] == -1) board[i][j] = 0;
            }
        }
    }
};

//Netease Gaming tool3, find cycle in Repository
//Try to implement DFS method
//And use DFS to save the path to see where is the cycle
class Solution_16 {
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
        vector<vector<int>> neighbors(numCourses);
        for (auto &p : prerequisites) {
            neighbors[p[1]].push_back(p[0]);
        }
        vector<bool> visited(numCourses);
        vector<int> path;
        vector<bool> trace(numCourses);

        for (int i = 0; i < numCourses; i++) {
            if (!dfs(neighbors, visited, path, trace, i)) {
                for (auto &p : path)
                    cout << p << ' ';
                return false;
            }
        }
        return true;
    }

private:
    bool dfs(vector<vector<int>> &neighbors, vector<bool> &visited, vector<int> &path, vector<bool> &trace, int cur) {
        if (!visited[cur] && !trace[cur]) {
            path.push_back(cur);
            visited[cur] = true;
            trace[cur] = true;
            for (auto &n : neighbors[cur]) {
                if (!dfs(neighbors, visited, path, trace, n)) {
                    return false;
                }
            }
            trace[cur] = false;
            path.pop_back();
            return true;
        } else if (trace[cur]) {
            path.push_back(cur);
            return false;
        } else {
            return true;
        }
    }
};


//Search in 2D matrix II
class Solution_17 {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        if (matrix.empty()) return false;
        return divide(matrix, 0, 0, matrix[0].size() - 1, matrix.size() - 1, target);
    }

private:
    bool divide(vector<vector<int>> &matrix, int left, int top, int right, int down, int target) {
        if (left > right || top > down) return false;
        int mid = (left + right) / 2;
        int row = top;
        while (row <= down && matrix[row][mid] <= target) {
            if (matrix[row][mid] == target) {
                return true;
            }
            row++;
        }
        return divide(matrix, left, row, mid - 1, down, target) ||
               divide(matrix, mid + 1, top, right, row - 1, target);
    }
};

//Also a rule method
class Solution_18{
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return false;
        int row = 0;
        int col = matrix[0].size() - 1;
        while(row < matrix.size() && col >= 0){
            if(matrix[row][col] < target){
                row++;
            }
            else if(matrix[row][col] > target){
                col--;
            }
            else{
                return true;
            }
        }
        return false;
    }
};

//minimum sum from top-left to bottom-right
class Solution_19{
public:
    int minPathSum(vector<vector<int>>& grid) {
        if(grid.empty()) return 0;
        int row = grid.size();
        int col = grid[0].size();
        for(int j = 1; j < col; j++){
            grid[0][j] += grid[0][j - 1];
        }
        for(int i = 1; i < row; i++){
            grid[i][0] += grid[i - 1][0];
            for(int j = 1; j < col; j++){
                grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
            }
        }
        return grid[row - 1][col - 1];
    }
};

//Find first bad version
//Check before go next
class Solution_20{
public:
    int firstBadVersion(int n) {
        int left = 1;
        int right = n;
        while(left < right){
            int mid = left + (right - left) / 2;
            if(isBadVersion(mid)){
                if(mid == 1 || isBadVersion(mid - 1)){
                    return mid;
                }
                right = mid - 1;
            }
            else{
                left = mid + 1;
            }
        }
        return left;
    }
private:
    bool isBadVersion(int version){ return true;}
};


//LCA in binary tree
//Simple dfs, count left right and itself
class Solution_21{
public:
    struct TreeNode{
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int val) : val(val), left(nullptr), right(nullptr){}
    };
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root, p, q);
        return res;
    }
private:
    TreeNode *res;
    int dfs(TreeNode* node, TreeNode* p, TreeNode* q){
        if(!node) return 0;
        int cur = node == p || node == q ? 1 : 0;
        cur += dfs(node->left, p, q);
        cur += dfs(node->right, p ,q);
        if(cur == 2){
            res = node;
        }
        return cur >= 1 ? 1 : 0;
    }
};

//Also can record the parent
class Solution_22{
public:
    struct TreeNode{
        int val;
        TreeNode *left;
        TreeNode *right;
        explicit TreeNode(int val) : val(val), left(nullptr), right(nullptr){}
    };
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        unordered_map<TreeNode*, TreeNode*> parent;
        stack<TreeNode*> path;
        parent[root] = nullptr;
        path.push(root);
        while(!path.empty()){
            TreeNode *p = path.top(); path.pop();
            if(p->left){
                parent[p->left] = p;
                path.push(p->left);
            }
            if(p->right){
                parent[p->right] = p;
                path.push(p->right);
            }
        }
        unordered_set<TreeNode*> parents;
        while(p){
            parents.insert(p);
            p = parent[p];
        }

        while(parents.find(q) == parents.end()){
            q = parent[q];
        }
        return q;
    }
};

//LCA in BST
class Solution_23{
public:
    struct TreeNode{
        int val;
        TreeNode *left;
        TreeNode *right;
        explicit TreeNode(int val) : val(val), left(nullptr), right(nullptr){}
    };
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p->val > q->val){
            swap(p, q);
        }
        TreeNode *res = root;
        while(res->val < p->val || res->val > q->val){
            res = res->val < p->val ? res->right : res->left;
        }
        return res;
    }
};


//Longest palindrome subsequence
//From right to left is faster than left to right.. EMmm
class Solution_24{
public:
    int longestPalindromeSubseq(string s) {
        int len = s.length();
        vector<vector<int>> dp(len, vector<int>(len, 0));
        for(int i = len - 1; i >= 0; i--){
            dp[i][i] = 1;
            for(int j = i + 1; j < len; j++){
                if(s[i] == s[j]){
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
                else{
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][len - 1];
    }
};


//Longest palindrome substring
//use the algorithm that always expand from middle to both sides.
class Solution_25{
public:
    string longestPalindrome(string s) {
        int len = s.length();
        int left = 0;
        int right = 0;
        int max_left = 0;
        int max_length = 1;
        int next_start = 0;
        while(len - next_start > max_length / 2){
            left = right = next_start;
            while(right < len - 1 && s[right + 1] == s[right]) right++;
            next_start = right + 1;
            while(left > 0 && right < len - 1 && s[left -1] == s[right + 1]){
                left--;
                right++;
            }
            if(max_length < right - left + 1){
                max_length = right - left + 1;
                max_left = left;
            }
        }
        return s.substr(max_left, max_length);
    }
};

//Sort colors
//If there are so many colors, we use bucket as count... then traverse again.
//Here we only have three
//Here we should notice that. 0 and 2 is used to saving next 0 or 2...
//So outside condition should be idx_1 <= idx_2. since we don't know what the element in idx_2 now
//And since we always swap 2 to the end
//When meet 0. we just make idx_0++ and idx_1++
//Since now the element located at idx_1 is either 0 or 1... So we can just go to next one.

class Solution_26{
public:
    void sortColors(vector<int>& nums) {
        int size = nums.size();
        int idx_0 = 0;
        int idx_1 = 0;
        int idx_2 = size - 1;
        while(idx_1 <= idx_2){
            if(nums[idx_1] == 0){
                swap(nums[idx_1], nums[idx_0]);
                idx_0++;
                idx_1++;
            }
            else if(nums[idx_1] == 2){
                swap(nums[idx_1], nums[idx_2]);
                idx_2--;
            }
            else{
                idx_1++;
            }
        }
    }
};

//closest value in BTS
class Solution_27{
public:
    struct TreeNode{
        int val;
        TreeNode *left;
        TreeNode *right;
        explicit TreeNode(int val) : val(val), left(nullptr), right(nullptr){}
    };
    int closestValue(TreeNode* root, double target) {
        long long big = INT64_MAX;
        long long small = INT64_MIN;
        TreeNode* p = root;
        while(p){
            if(p->val > target){
                big = p->val;
                p = p->left;
            }
            else if(p->val < target){
                small = p->val;
                p = p->right;
            }
            else{
                return p->val;
            }
        }
        if(big - target < target - small)
            return big;
        else
            return small;
    }

};


//next permutation
class Solution_28{
public:
    void nextPermutation(vector<int>& nums){
        int i = nums.size() - 2;
        while(i >= 0 && nums[i + 1] <= nums[i]) i--;
        // two situation. -1 or >=0
        if(i >= 0){
            int j = nums.size() - 1;
            while(j >= 0 && nums[j] <= nums[i]) j--;
            swap(nums[i], nums[j]);
        }
        //no matter -1 or >= we always reverse from i + 1
        reverse(nums.begin() + i + 1, nums.end());
    }
};



int main() {
}