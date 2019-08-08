//
// Created by Ke Ye on 2019-08-08.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution{
public:
    string numberToWords(int num) {
        if(!num) return "Zero";
        return generateWord(num).substr(1);
    }

private:
    vector<string> dec_unit{"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                            "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen",
                            "Eighteen", "Nineteen"};
    vector<string> dec{"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    string generateWord(int num){
        if(num >= 1000000000){
            return generateWord(num / 1000000000) + " Billion" + generateWord(num % 1000000000);
        }
        else if(num >= 1000000){
            return generateWord(num / 1000000) + " Million" + generateWord(num % 1000000);
        }
        else if(num >= 1000){
            return generateWord(num / 1000) + " Thousand" + generateWord(num % 1000);
        }
        else if(num >= 100){
            return generateWord(num / 100) + " Hundred" + generateWord(num % 100);
        }
        else if(num >= 20){
            return " " + dec[num / 10] + generateWord(num % 10);
        }
        else if(num >= 1){
            return " " + dec_unit[num];
        }
        return "";
    }
};

int main() {

}