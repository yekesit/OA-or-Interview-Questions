//
// Created by Ke Ye on 2019-07-23.
//

#include <iostream>
#include <vector>

// Sqrt with precision

class Solution_0{
public:
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
};


//LT-114 Flatten Binary Tree To linked List

//First thougth is, use a previous pointer to save previous node
//Then  keep using previous->right = current node to build the whole list.
//But here are many redundant operations.. Emmmm
//Try to improve.
//Finish improvement. EMmmm Nice. for recursionm focus on current node... Emmm
// class Solution {
// public:
//     void flatten(TreeNode* root) {
//         if(!root) return;
//         p = root;
//         TreeNode *right = root->right;
//         helper(root->left);
//         root->left = nullptr;
//         helper(right);
//     }

// private:
//     TreeNode* p;
//     void helper(TreeNode* root){
//         // if(!root) return;
//         // p->right = root;
//         // p = root;
//         // TreeNode *right = root->right;
//         // p->right = p->left;
//         // p->left = nullptr;
//         // helper(p->right);
//         // helper(right);
//         if(!root) return;
//         p->right = root;
//         p = root;
//         TreeNode *right = root->right;
//         helper(root->left);
//         root->left = nullptr;
//         helper(right);
//     }
// };

//Also can do it in iteration.
//It's just, for every node, if we have left child. Then finally there is a node in left subtree
//which will finally connect to right child.
//So we can go to left child, and then find the most right child, then connect to the current node  right child
//Then resolve current node which is left > right and left = nullptr
//A little slow but code is concise and nice. EMmm

class Solution_1{
public:
    void flatten(TreeNode* root) {
        TreeNode *cur = root;
        while(cur){
            if(cur->left) {
                TreeNode *left = cur->left;
                while(left->right){
                    left = left->right;
                }
                left->right = cur->right;
                cur->right = cur->left;
                cur->left =nullptr;
            }
            cur = cur->right;
        }
    }
};


//LT-214
//I think we can use longest common prefix to solve the problem
//WHich is ...reverse the original string and assign it to a new one.
//Then get the longest common prefix, which means we find a longest subpalindrome here. then we just need to add
//others left
//But still On^2.. since it's dp is n^2.. Emmmm

//They use a KMP to put original and reverse one together... So we just use KMP for new string here.
class Solution_2 {
public:
    string shortestPalindrome(string s) {
        string tmp = s;
        reverse(tmp.begin(), tmp.end());
        string new_str = s + "#" + tmp;

        vector<int> f(new_str.length(), -1);
        int j = -1;
        int i = 0;
        while(i < new_str.length() - 1){
            if(j == -1 || new_str[i] == new_str[j]){
                i++;
                j++;
                f[i] = j;
            }
            else{
                j = f[j];
            }
        }
        string res = tmp.substr(0, tmp.length() - f.back() - 1) + s;
        return res;
    }
};

//can not do it directly with two strings... Since the first part of KMP only used for the pattern itself
//If two stirngs are not same... Then the f we generate will be wrong...
//Since when we combine them together, when we find failuer here, we chosse next[j]. but here next[j] is in
//the new string combined with two stirngs.... So here is a trick.... Emmm Well, I can not come up with it.. LOL

//Follow up, insert in any place
//LCS find maximum common sequence.. Then minus it.
//https://www.geeksforgeeks.org/minimum-insertions-to-form-a-palindrome-dp-28/



//LT-213

//Steal twice 0 >> n - 2  and 1 >> n-1. Since there is a circle
class Solution_3 {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int size = nums.size();
        if(size == 1) return nums[0];

        return max(robHelper(nums, 0, size - 2), robHelper(nums, 1, size - 1));

    }
private:
    int robHelper(vector<int>& nums, int l, int r){
        int pre_max = 0;
        int cur_max = 0;
        for(int i = l; i <= r; i++){
            int tmp = cur_max;
            cur_max = max(pre_max + nums[i], cur_max);
            pre_max = tmp;
        }
        return cur_max;
    }
};


//LT-22 parenthese
class Solution_4 {
public:
    vector<string> generateParenthesis(int n) {
        int left = 0, right = 0;
        vector<string> res;
        string cur;
        helper(res, cur, left, right, n);
        return res;
    }

private:
    void helper(vector<string>& res, string& cur, int& left, int& right, int n){
        if(left == n && right == n){
            res.push_back(cur);
            return;
        }

        if(left < n){
            cur += '(';
            left++;
            helper(res, cur, left, right, n);
            cur.pop_back();
            left--;
        }

        if(right < left){
            cur += ')';
            right++;
            helper(res, cur, left, right, n);
            cur.pop_back();
            right--;
        }
    }
};


//LT-611 valid triangle number
class Solution_5 {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int size = nums.size();
        int res = 0;
        for(int i = 0; i < size - 2; i++){
            if(!nums[i]) continue;
            int left = i + 1;
            int right = i + 2;
            while(left < size - 1){
                while(right < size && nums[i] + nums[left] > nums[right]) right++;
                res += right - left - 1;
                left++;
            }
        }
        return res;
    }
};


//LT-206 reverse linked list
//Review iteration and recursion
// class Solution{
// public:
//     ListNode* reverseList(ListNode* head) {
//         if(!head || !head->next) return head;

//         ListNode *pre = nullptr;
//         ListNode *cur = head;
//         ListNode *next;
//         while(cur){
//             next = cur->next;
//             cur->next = pre;
//             pre = cur;
//             cur = next;
//         }
//         return pre;
//     }
// };


class Solution_6 {
public:
    ListNode* reverseList(ListNode* head){
        // if(!head || !head->next) return head;
        // ListNode *p = head;
        // head = reverseList(head->next);
        // p->next->next = p;
        // p->next = nullptr;
        // return head;

        if(!head || !head->next) return head;
        ListNode *p = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return p;
    }
};


//LT-901 单调栈， 涉及某个东西能持续多少天

class StockSpanner {
public:
    StockSpanner() {

    }

    int next(int price) {
        int count = 1;
        while(!keep.empty() && price >= keep.top().first ){
            count += keep.top().second; keep.pop();
        }
        keep.push({price, count});
        return count;
    }

private:
    stack<pair<int, int>> keep;
};




//LT-117. Use next to get bfs

class Solution_7 {
public:
    Node* connect(Node* root) {
        Node *cur = root;
        Node *next_dummy = new Node();
        next_dummy->next = nullptr;
        Node *p = next_dummy;
        while(cur){
            if(cur->left){
                p->next = cur->left;
                p = p->next;
            }
            if(cur->right){
                p->next = cur->right;
                p = p->next;
            }
            if(cur->next){
                cur = cur->next;
            }
            else{
                cur = next_dummy->next;
                next_dummy->next = nullptr;
                p = next_dummy;
            }
        }
        return root;
    }
};

//Path sum I II not hard
//Path sum III should use array method here but remember to delete the content in hashmap


class Solution_8 {
public:
    int pathSum(TreeNode* root, int sum){
        unordered_map<int, int> pre_sum;
        pre_sum[0] = 1;
        return subtree(root, pre_sum, sum, 0);
    }
private:
    int subtree(TreeNode* root, unordered_map<int, int>& pre_sum, int sum, int prefix){
        if(!root) return 0;
        root->val += prefix;
        int cur_res = pre_sum[root->val - sum];
        pre_sum[root->val]++;
        cur_res += subtree(root->left, pre_sum, sum, root->val);
        cur_res += subtree(root->right, pre_sum, sum, root->val);
        pre_sum[root->val]--; // Nice backtracking here.... change to another subtree
        return cur_res;
    }
};


//If a number can be two primes sum
//Count prime first then two pointers.
class Solution_9 {
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


//Coin change problem....
//Find the maximum number can not be represented by groups
//lcm(a ,b) + lcm(b, c) - a - b -  c
// lcm need gcd


//Diameter of a Binary Tree
//weight 1 path sum in a tree
//Find the largest one. pass through a root


//Square free
//https://www.geeksforgeeks.org/square-free-number/
//Solve 2 first ..since 4 6 8 10... all contain 2 don't need check even
//Then odd one by one

//Serialize  deserialize BST
//Basic solution, but add BST rule here. since for node in bst, it should > left and < right
//So if we do preorder for original tree, then when we build the tree, we can use such rule to save much space.
//And here is a method that using 4byts node...
//Since in BST, we can only care about the number(the rule above), and assume the number won't exceed a range
//Then we can use a simple 4bytes string to describe the node.. Save space
//For example assume the number is below 2 ^ 31 - 1 here we use 32 bits >> 4bytes to describe a number
//So if we have XXXXXXXX XXXXXXXX XXXXXXXX XXXXXXXX. then for each, is a 1 byte number. fron 0 - 255
//So this is a good chance for us to use a 0-255 character to stand for that number. then finally each number can be
//compressed into 4 bytes and not like general ways 12138 >> "12138" 5 bytes.
//Try it

// class Codec {
// public:

//     // Encodes a tree to a single string.
//     // Preorder to serialize, and use BST rule to save space
//     string serialize(TreeNode* root) {
//         if(!root) return "";
//         return to_string(root->val) + " " + serialize(root->left) + serialize(root->right);
//     }

//     // Decodes your encoded data to tree.

//     TreeNode* helper(vector<int>& nums, int& idx, int left, int right){
//         if(idx == nums.size() || nums[idx] <= left || nums[idx] >= right) return nullptr;

//         TreeNode *root = new TreeNode(nums[idx++]);
//         root->left = helper(nums, idx, left, root->val);
//         root->right = helper(nums, idx, root->val, right);
//         return root;
//     }


//     TreeNode* deserialize(string data) {
//         if(data.empty()) return nullptr;
//         istringstream str(data);
//         string tmp;
//         vector<int> nums;
//         while(str >> tmp){
//             nums.push_back(stoi(tmp));
//         }
//         int idx = 0;
//         return helper(nums, idx, INT_MIN, INT_MAX);
//     }
// };

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));



//If use 4 bytes method, we should take care of the sign....
//If this is a negative number ... if we don't transform it to unsigned.
//Then it appears as completement code in memory. then there is mistake....
//Also when we go back from string. change it to unsigned char... or if the first digit is 1... it will be minus
//number ... then wrong..
class Codec{
public:
    string serialize(TreeNode* root) {
        if(!root) return "";
        string cur(4, ' ');
        for(int i = 0; i < 4; i++){
            cur[i] = (unsigned int)root->val >> ((3 - i) * 8);
        }
        return cur + serialize(root->left) + serialize(root->right);
    }

    TreeNode* helper(string& data, int& idx, int left, int right){
        if(idx == data.length()) return nullptr;
        int num = 0;
        for(int i = 0; i <= 3; i++){
            num += (unsigned char)data[idx + i] << ((3 - i) * 8);
        }
        if(num <= left || num >= right) return nullptr;
        idx += 4;
        TreeNode *root = new TreeNode(num);
        root->left = helper(data, idx, left, num);
        root->right = helper(data, idx, num, right);
        return root;
    }


    TreeNode* deserialize(string data) {
        int idx = 0;
        return helper(data, idx, INT_MIN, INT_MAX);
    }
};



//LT-712
class Solution_10 {
public:
    int minimumDeleteSum(string s1, string s2) {
        int row = s1.length();
        int col = s2.length();
        vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));
        for(int i = 1; i <= col; i++){
            dp[0][i] += dp[0][i - 1] + s2[i - 1];
        }
        for(int i = 1; i <= row; i++){
            dp[i][0] += dp[i - 1][0] + s1[i - 1];
        }

        for(int i = 1; i <= row; i++)
            for(int j = 1; j <= col; j++){
                if(s1[i - 1] == s2[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else{
                    dp[i][j] = min(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]);
                }
            }
        return dp[row][col];
    }
};


//Kruskal union find
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


//LC substring and LC subsequence
class Solution_11{
public:
    int LCSubstring(string& a , string& b){
        int row = a.length();
        int col = b.length();
        vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));
        int max_length = 0;
        for(int i = 1; i <= row; i++)
            for(int j = 1; j <= col; j++){
                if(a[i - 1] == b[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    max_length = max(max_length, dp[i][j]);
                }
            }
        return max_length;
    }


    int LCSubsequence(string& a, string& b){
        int row = a.length();
        int col = b.length();
        vector<vector<int>> dp(row + 1, vector<int>(col + 1, 0));
        for(int i = 1; i <= row; i++)
            for(int j = 1; j <= col; j++){
                if(a[i - 1] == b[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else{
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        return dp[row][col];
    }
};


//LT-723 Candy Crush
class Solution_12 {
public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        int row = board.size();
        int col = board[0].size();
        bool modify = true;
        while(modify){
            modify = false;
            for(int i = 0; i < row; i++){
                for(int j = 0; j < col; j++){
                    if(!board[i][j]) continue;
                    int cur = abs(board[i][j]);
                    if(j + 2 < col && abs(board[i][j + 1]) == cur && abs(board[i][j + 2]) == cur){
                        board[i][j] = board[i][j + 1] = board[i][j + 2] = -cur;
                        modify = true;
                    }
                    if(i + 2 < row && abs(board[i + 1][j]) == cur && abs(board[i + 2][j]) == cur){
                        board[i][j] = board[i + 1][j] = board[i + 2][j] = -cur;
                        modify = true;
                    }
                }
            }
            if(modify){
                for(int j = 0; j < col; j++){
                    int bottom = row - 1;
                    for(int i = row - 1; i >= 0; i--){
                        if(board[i][j] > 0){
                            board[bottom--][j] = board[i][j];
                        }
                    }
                    while(bottom >= 0){
                        board[bottom--][j] = 0;
                    }
                }
            }
        }
        return board;
    }
};

//Find adjacent absolute difference equals target
class Solution_13{
public:
    void helper(vector<string>& res, string& cur, int target, int idx, int length){
        if(idx == length){
            if(target == 0){
                res.push_back(cur);
            }
            return;
        }

        for(char i = '0' ; i <= '9'; i++){
            if(abs(cur[idx - 1] - i) <= target){
                cur += i;
                helper(res, cur, target - abs(cur[idx - 1] - i), idx + 1, length);
                cur.pop_back();

            }
        }
    }


    vector<string> findNum(int length, int target){
        vector<string> res;
        string cur;
        for(char i = '1'; i <= '9'; i++) {
            cur += i;
            helper(res, cur, target, 1, length);
            cur.pop_back();
        }
        return res;
    }
};

//Find most days a temperature keep higher
class Solution_14{
public:
    vector<int> findDaysHigherBefore(vector<int>& input){
        stack<int> idx;
        vector<int> res(input.size());
        for(int i = input.size() - 1; i >= 0; i--){
            while(!idx.empty() && input[i] > input[idx.top()]){
                int cur = idx.top(); idx.pop();
                res[cur] = cur - i - 1;
            }
            idx.push(i);
        }
        int i = -1;
        while(!idx.empty()){
            int cur = idx.top(); idx.pop();
            res[cur] = cur - i - 1;
        }
        return res;
    }
};

//LT-739 find next warmer day
class Solution_15 {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        stack<int> idx;
        vector<int> res(T.size());
        for(int i = 0; i < T.size(); i++){
            while(!idx.empty() && T[i] > T[idx.top()]){
                res[idx.top()] = i - idx.top();
                idx.pop();
            }
            idx.push(i);
        }
        return res;
    }
};

//Read 4, and Read 4 follow up
int read4(char *buf);

class Solution_16 {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    int read(char *buf, int n) {
        int res = 0;
        while (n > 0) {
            int tmp = min(read4(buf), n);
            res += tmp;
            buf += tmp;
            if (tmp < 4)
                break;
            n -= 4;
        }
        return res;
    }
};


class Solution_17 {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    char buffer[4];
    int idx = 0;
    int len = 0;
    int read(char *buf, int n) {
        int i = 0;
        while(i < n){
            if(idx == len){
                idx = 0;
                len = read4(buffer);
                if(!len) break;
            }
            buf[i] = buffer[idx];
            i++;
            idx++;

        }
        return i;
    }
};

//522. Longest Uncommon Subsequence II

class Solution_18 {
public:
    int findLUSlength(vector<string>& strs) {
        sort(strs.begin(), strs.end(), [](string& s1, string& s2){ return s1.length() > s2.length(); });
        for(int i = 0; i < strs.size(); i++){
            bool flag = true;
            for(int j = 0; j < strs.size(); j++){
                if(i == j) continue;
                if(isSubsequence(strs[i], strs[j])){
                    flag = false;
                    break;
                }
            }
            if(flag){
                return strs[i].length();
            }
        }
        return -1;
    }
private:
    bool isSubsequence(string& s1, string& s2){
        int j = 0;
        for(int i = 0; i < s2.length() && j < s1.length(); i++){
            if(s1[j] == s2[i]){
                j++;
            }
        }
        return j == s1.length();
    }
};