//
// Created by Ke Ye on 2019-06-14.
//

/*
 * Input : s = "geeksforgeeks"
        c = 'e'
    Output : s = "gksforgks"
 */

#include <iostream>

using namespace std;


void removeChar(string& input, char target){
    int j = 0;
    for(int i = 0; i < input.length(); i++){
        if(input[i] != target){
            input[j] = input[i];
            j++;
        }
    }
    input[j] = '\0';
    cout << input << endl;
}



int main(){
    //in-place method
    string input = "geeksforgeeks";
    char target = 'e';
    removeChar(input, target);


}

