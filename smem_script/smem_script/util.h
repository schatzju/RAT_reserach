//
//  Utilities.hpp
//  smem_script
//
//  Created by Jule Schatz on 4/6/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#ifndef Utilities_hpp
#define Utilities_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>

using namespace std;

//Hash for string string pair
struct pairHasher {
    std::size_t operator()(const std::pair<string, string> &val) const {
        return hash<string>()(val.first + "." + val.second);
    }
};


struct int_pair_compare{
    bool operator()(pair<int, pair<string, string>> a, pair<int, pair<string, string>> b){
        int first_int = a.first;
        int sec_int = b.first;
        
        if(first_int > sec_int) return true;
        else return false;
    }
};

struct pair_compare{
    bool operator()(pair<string, int> a, pair<string, int> b){
        if(a.second > b.second){
            return false;
        }
        else if(a.second < b.second){
            return true;
        }
        else{
            return true;
        }
    }
};

bool find_vect(vector<int> vec, int item);

//returns true if word1word2 is a word in the dictionary
bool check_compound(string word1, string word2, unordered_set<string> &dictionary);

//returns true if word1word2 is a word already seen in the dataset
bool check_compound_unigrams(string word1, string word2, unordered_map<string, int> &unigrams);

void removeWhitespace(std::string& str);



#endif /* Utilities_hpp */
