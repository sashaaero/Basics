#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool _is(string letters, char c){
    c = tolower(c);
    for(auto it = letters.begin(); it != letters.end(); it++)
        if(*it == c)
            return true;
    return false;
}

bool vowel(char c){
    string letters = "euioa";
    return _is(letters, c);
}

bool consonant(char c){
    string letters = "qwrtypsdfghjklzxcvbnm";
    return _is(letters, c);
}

bool is_valid(string data){
    bool (*even)(char), (*odd)(char);
    if(vowel(data[0])){
        even = &vowel;
        odd = &consonant;
    } else if(consonant(data[0])) {
        even = &consonant;
        odd = &vowel;
    } else {
        return false;
    }
    for(size_t i = 0; i < data.length(); i += 2)
        if(!even(data[i])) return false;

    for(size_t i = 1; i < data.length(); i += 2)
        if(!odd(data[i])) return false;

    return true;
}

void lab8(){
    vector<string> words;
    string line;
    ifstream file("../Basics/text.txt");

    if(file.is_open()){
        while(getline(file, line, ' ')){
            if(is_valid(line)){
                words.push_back(line);
            }
        }
    }
    for(auto it = words.begin(); it != words.end(); it++){
        cout << *it << " ";
    }
}
