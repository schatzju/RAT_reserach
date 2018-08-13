//
//  Utilities.cpp
//  smem_script
//
//  Created by Jule Schatz on 4/6/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#include "util.h"
using namespace std;

bool find_vect(vector<int> vec, int item){
    
    int half = (int)vec.size()/2;
    
    if(vec[half] == item){
        return true;
    }
    
    if(vec.size() == 1) return false;
    
    if(vec[half] > item){
        return find_vect(vector<int>(vec.begin(), vec.begin()+ half), item);
    }
    if(vec[half] < item){
        return find_vect(vector<int>(vec.begin()+ half, vec.end()), item);
    }
    
    return false;
}


bool check_compound(string word1, string word2, unordered_set<string> &dictionary){
    string word_new = word1 + word2;
    
    if(dictionary.find(word_new) != dictionary.end()){
        return true;
    }
    
    return false;
}

bool check_compound_unigrams(string word1, string word2, unordered_map<string, int> &unigrams){
    string word_new = word1 + word2;
    
    if(unigrams.find(word_new) != unigrams.end()){
        return true;
    }
    
    return false;
}

void removeWhitespace(std::string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
            str.erase(i, 1);
            i--;
        }
    }
}
