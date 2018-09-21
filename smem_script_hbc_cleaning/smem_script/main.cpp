//
//  main.cpp
//  smem_script
//
//  Created by Jule Schatz on 4/6/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include "single_db.h"
#include "double_db.h"
#include "dictionary.h"
#include "collocation_compound.h"
#include "RAT_solution_check.h"
#include "read_data.h"
#include "correction.hpp"

using namespace std;

void hbc(unordered_set<string> &dictionary, bool single_, bool double_, bool dict_on, vector<int> subset = {}){
    if( !single_ && !double_) return;
    
    string extra = "";
    
    //all unique words in the data and its unique identifier
    unordered_map<string, int> unigrams_hbc;
    
    //maps word1, word2 to it's association weight.
    unordered_map< pair<string, string> , int, pairHasher> word_word_weight_hbc;
    
    
    if(subset.size() > 0){
        read_hbc_data_subset(dictionary, word_word_weight_hbc, unigrams_hbc, dict_on, subset);
        extra = "_subset";
    }
    else{
        read_hbc_data(dictionary, word_word_weight_hbc, unigrams_hbc, dict_on);
    }
    

    //---------------------single-----------------------//
    if(single_){
        unordered_map< string, int> hbc_single_fan;
        unordered_map< pair<string, string> , int, pairHasher> word_word_weight_hbc_single = word_word_weight_hbc;
        if(dict_on){
            single_db(word_word_weight_hbc_single, unigrams_hbc, hbc_single_fan, "hbc_single" + extra);
        }
        else{
            single_db(word_word_weight_hbc_single, unigrams_hbc, hbc_single_fan, "hbc_single_trash" + extra);
        }
        cout << endl;
    }
    
    //---------------------double-----------------------//
    if(double_){
        unordered_map< string, int> hbc_double_fan;
        unordered_map< pair<string, string> , int, pairHasher> word_word_weight_hbc_double = word_word_weight_hbc;
        double_db(word_word_weight_hbc_double, unigrams_hbc, hbc_double_fan, "hbc_double");
        
        cout << endl;
    }
}

void COCA_TG(unordered_set<string> &dictionary){
    unordered_map<string, int> unigrams_COCA_TG;
    unordered_map< pair<string, string> , int, pairHasher> word_word_weight_COCA_TG;
    read_COCA_TG_data(dictionary, word_word_weight_COCA_TG, unigrams_COCA_TG, 600);
    
    unordered_map< string, int> COCA_TG_double_fan;
    double_db(word_word_weight_COCA_TG, unigrams_COCA_TG, COCA_TG_double_fan, "COCA_TG_double");
}


int main(){
    cout << "starting script..." << endl;
    unordered_set<string> dictionary;
    
    create_dictionary(dictionary, "words.txt");
    
    //collocation check is not currently being done because the collocation dataset seemed incomplete
    //unordered_map<string, unordered_set<string> > collocations;
    //create_collocations(collocations);
    
    bool run_single = true;
    bool run_double = false;

    //cout << "not dict and subset" << endl;


   // vector<int> subset = {7, 18, 32, 53, 128};
    vector<int> subset;

    
    for(int i =1; i < 145; i++){
        subset.push_back(i);
    }
    
    cout << "\nsubset with dict" << endl;
    hbc(dictionary, run_single, run_double, true, subset);
    
    cout << "\nsubset with no dict" << endl;
    hbc(dictionary, run_single, run_double, false, subset);

    cout << "\nwith dict" << endl;
    hbc(dictionary, run_single, run_double, true);
    
    cout << "\nno dict" << endl;
    hbc(dictionary, run_single, run_double, false);

    
//    cout <<"WITH DICT" << endl;
//    hbc(dictionary, run_single, run_double, true);

    
    //COCA_TG(dictionary);
    
}
