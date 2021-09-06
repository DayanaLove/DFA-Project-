#include<algorithm>
#include <regex>
#include <unordered_map>
#include "FinalProject.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<iostream>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>
#include <iterator>


using namespace std;

char removeBrakets[] = {'{', ',', '}'};  // Array of characters to be removed from the string.
vector<string> fileinput;  // the linkedlist that holds each line of the text file 
string file;
int transfunc = -4;  // this variable holds the number of transition functions
string stop = "stop";

// stops the program
void incorrect_input(){
    printf("Program Stopped.");
    exit(0);
}

// called if user does not have a cl arg for file input. 
void check_input(){  
    printf("Please input a textfile");
    cin >> file;
}

// checks if the string is accepted
void is_accepted(char currState){
    int isaccept=0;
    //string reformatting
    for(int i=0; i<3; i++) {
        fileinput[3].erase(remove(fileinput[3].begin(), fileinput[3].end(), removeBrakets[i]), fileinput[3].end());
    }

    // iterates through the accept states string and increments isaccepts if there's a match.
    for(int i=0; i<fileinput[3].length(); i++){
        if(currState == fileinput[3][i]){
            isaccept++;
        }
    }
    if(isaccept>=1){
        cout << "String Accepted" << endl; 
    } else {
        cout << "String Rejected" << endl;
     }
}

// this method handles the state transitions. 
char state_changes(string input, char currState, int c){
    int len = input.length();
    for(int i=0; i<len; i++){
        for(int j=4; j<c; j++){
            if(currState == fileinput[j][0] && input[i] == fileinput[j][1]){
                cout << "("<< currState << "," << input[i] << ")" << "->";
                currState = fileinput[j][2];
                cout << currState << endl;
                break;
            }

        }
    }
    return currState;
}

// this method reformats the transition functions inputs.
void transitions_func(int c){
    int key; 
    char charArr[] = {'(', ',', '-', '>', ')'};  
    for (int j=4; j<c; j++) {
        for(int i=0; i<5; i++) {
            fileinput[j].erase(remove(fileinput[j].begin(), fileinput[j].end(), charArr[i]), fileinput[j].end());
        }
    }
}

// this method checks the if the language of user's input valid
void language(string s){
    string lang = fileinput[0];
    // Reformating the string for the regex
    for(int i=0; i<3; i++) {
        lang.erase(remove(lang.begin(), lang.end(), removeBrakets[i]), lang.end());
    }
    
    lang.insert(lang.begin(),'[');
    lang.insert(lang.end(),']');  
    lang.insert(lang.end(),'+');


    //creating regex pattern
    const regex pattern(lang);
    //checking if the language is valid
    
     if(!regex_match(s, pattern)){
          cout<< "The Language is invalid. String Rejected" << endl;
          exit(0);
         }
}

// this method handles the file inputs 
void file_input(){
    // inputs file 
    ifstream infile;
    infile.open(file); 
    
    // If the fileinput fails the user is prompted to try agin unil input is successful, unless user enters "stop";
     while(infile.fail()) { 
        printf("Input Failed. Try again or type stop.");
        cin >> file; 
        infile.open(file);  
        if(file.compare(stop)==0){
            incorrect_input();
        }
    } 

    // inputs each line of the file into string vector. 
    string tmp; 
    while(getline(infile, tmp)) {
            fileinput.push_back(tmp);
            transfunc++; //initialized at -4, and increments for each line to hold the amount to fold the amount of trans funcs
        }
    
}

int main(int argc, char* argv[]) {
    // checks for commmand line arg. if there is no arg program call check_input.
    if(argc!=2) {         
       check_input();
    }else {
        file=argv[1];
    }
     
    file_input(); 
    struct user user;   // struct hold user's input and current state
    cout << "Please input your string" << endl;
    cin >> user.userInput;
    language(user.userInput); 
    int counter = (transfunc + 4); 
    transitions_func(counter);
    user.currentState = fileinput[2][0];
    user.currentState = state_changes(user.userInput, user.currentState, counter);
    is_accepted(user.currentState);


   

}