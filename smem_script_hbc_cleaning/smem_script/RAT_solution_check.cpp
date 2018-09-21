//
//  RAT_solution_check.cpp
//  smem_script
//
//  Created by Jule Schatz on 4/6/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//
#include "RAT_solution_check.h"

bool in_map(string word1, string solution, unordered_map< pair<string, string> , int, pairHasher> & word_word_weight){
    
    pair<string, string> oneway(word1, solution);
    
    auto it1 = word_word_weight.find(oneway);
    
    if(it1 != word_word_weight.end()){
        return true;
    }
    return false;
}

void rat_check(unordered_map< pair<string, string> , int, pairHasher> & word_word_weight, string out_file_name){
    
    ofstream outFile;
    outFile.open(out_file_name);
    
    ifstream inFile;
    inFile.open("raw_144.txt");
    
    string word1, word2, word3, solution;
    
    while(inFile >> word1 >> word2 >> word3 >> solution){
        outFile << word1 << ", " << word2 << ", " << word3 << ", ";
        
        if(in_map(word1, solution, word_word_weight) && in_map(word2, solution, word_word_weight) && in_map(word3, solution, word_word_weight)){
            outFile << " 1" << endl;
        }
        if(in_map(solution,word1, word_word_weight) && in_map(solution,word2, word_word_weight) && in_map(solution, word3, word_word_weight)){
            outFile << " 1" << endl;
        }
        else{
            outFile << " 0" << endl;
        }
    }
    
}
