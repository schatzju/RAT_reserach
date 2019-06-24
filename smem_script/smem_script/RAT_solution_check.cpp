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
    
    ofstream outFileAny;
    outFileAny.open("solution_files/" + out_file_name);
    outFileAny << "id,word1,word2,word3,forward,backward,both,either" << endl;
    
    ifstream inFile;
    inFile.open("raw_144.txt");
    
    ofstream outFileEither;
    outFileEither.open("solution_files/" + out_file_name + "_subRatEither");
    
    string word1, word2, word3, solution;
    int count = 1;
    

    while(inFile >> word1 >> word2 >> word3 >> solution){
        outFileAny << count << "," << word1 << "," << word2 << "," << word3 << ",";
        bool forward = false;
        bool backward = false;
        
        if(in_map(word1, solution, word_word_weight) && in_map(word2, solution, word_word_weight) && in_map(word3, solution, word_word_weight)){
            outFileAny << "1,";
            forward = true;
        }
        else{
            outFileAny << "0,";
        }
        
        if(in_map(solution,word1, word_word_weight) && in_map(solution,word2, word_word_weight) && in_map(solution, word3, word_word_weight)){
            outFileAny << "1,";
            backward = true;
        }
        else{
            outFileAny << "0,";
        }
        
        if(forward && backward){
            outFileAny << "1,";
        }
        else{
            outFileAny << "0,";
        }
        if(forward || backward){
            outFileAny << "1";
            outFileEither << word1 << " " << word2 << " " << word3 << " " << solution << endl;
        }
        else{
            outFileAny << "0";
        }
        
        count++;
        outFileAny << endl;
    }
    
}
