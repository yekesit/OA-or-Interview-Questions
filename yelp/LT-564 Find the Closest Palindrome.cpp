//
// Created by Ke Ye on 2019-08-08.
//

#include <iostream>

using namespace std;

/* After get the thought, the problem is not hard. The core is to generate from large part to small part since
 * we need the least difference. eg. 123 >> 323, 121. Obviously 121 is good
 * Then there are some other situations. If there is a 9 in middle like XX9YY, then 10001 may be the best solution.
 * Or if there is a 0 in middle like XX0YY, then 9999 may be the best solution. (Well, math rule, I get it from solution).
 * Then we want to modify some when there is 0 and 9.
 * Then other situations occur. for single character, we also should get one more or one less... So we should not only
 * apply above rule to '9' and '0'. Should for all numbers.
 * Then one more situation here, for plus one, everything is ok. for minus one, generally it is ok. But when the number
 * is 1X..... the first 1 will be 0.... then we may generate 00 as final solution... this only occurs on 10 and 11
 * Since for 10 and 11 the answer is 9. But we can't get it directly, so we should add one more condition here to check
 * whether after minus the string is only 0 here. But if we do this, the problem will occur on '1'... Since for '1' the
 * answer is '0'. So finally, to make the code concise and reasonable, we make '1' outside then
 * Since if we don't check '0' here, for 1X we all get 00. Maybe the solution is right. but the case is not reasonable
 * So.... drag out 1 here
 * 3 cases here: According to math rule!!!!
 * case 1: XXCYY >> XXCXX
 * case 2: MN9YY >> ST0TS or 100001
 * case 3: MN0YY >> ST9TS or 99999
 * */


class Solution{
public:
    string nearestPalindromic(string n) {
        if(n == "1") return "0";

        int len = n.length() / 2; // Used to generate small part
        long num = stol(n);
        string small_part_1(len, '0'); // "000000" part used for case 2
        string small_part_2(len, '9'); // "999999" part used for case 3
        string large_part = n.substr(0, n.length() - len); // The large part combined with small to generate final string.
        long large_part_num = stol(large_part); // Use this num to plus one, minus one to generate case 2 and 3
        string num1_str, num2_str, num3_str;
        long num1, num2, num3;
        int diff1 = INT_MAX, diff2 = INT_MAX, diff3 = INT_MAX;

        // Case 1
        num1_str = large_part + small_part_1; // both 1 and 2 are ok, just make a whole string here
        generatePalindrome(num1_str);
        num1 = stol(num1_str);
        diff1 = abs(num1 - num);
        if(!diff1) diff1 = INT_MAX; // not itself

        // Case 2
        num2_str = to_string(large_part_num + 1) + small_part_1;
        generatePalindrome(num2_str);
        num2 = stol(num2_str);
        diff2 = abs(num2 - num);

        // Case 3
        num3_str = to_string(large_part_num - 1) == "0" ? "9" : to_string(large_part_num - 1) + small_part_2;
        generatePalindrome(num3_str);
        num3 = stol(num3_str);
        diff3 = abs(num3 - num);

        // The answer should be smallest one with smallest difference So check case 3 first
        if(diff3 <= diff2 && diff3 <= diff1)
            return num3_str;
        else if(diff1 <= diff2 && diff1 <= diff3)
            return num1_str;
        else
            return num2_str;

    }

private:
    //Used to modify string, since I don't want to reverse or write some others to make code ugly...
    void generatePalindrome(string& s){
        for(int i = 0, j = s.length() - 1; i < j; i++, j--)
            s[j] = s[i];
    }
};



int main() {

}