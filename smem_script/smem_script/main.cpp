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
#include <ctime>
#include "single_db.h"
#include "double_db.h"
#include "dictionary.h"
#include "collocation_compound.h"
#include "RAT_solution_check.h"
#include "read_data.h"
#include "correction.h"
#include "frequency_data.hpp"

using namespace std;


void hbc(unordered_set<string> &dictionary, bool single_, bool double_, bool dict_on, string file_in, int frequencyTime,  double frequencyScale, string fileName){

    string file_out = fileName;
    
    if(frequencyTime != 0){
         file_out = "freqTime" + to_string(frequencyTime) + "_freqScale"+ to_string(frequencyScale) + fileName;
    }
        
    //all unique words in the data and its unique identifier.
    unordered_map<string, int> unigrams_hbc;
    
    //maps word1, word2 to its association weight.
    unordered_map< pair<string, string> , int, pairHasher> word_word_weight_hbc;
    
    //maps words to known lemmas
    unordered_map<string, string> word_lemma;
    
    //maps lemmas to their frequency
    unordered_map<string, int> lemma_freq;
    
    //maps words to their frequency
    unordered_map<string, int> word_freq;
    
    //fills word_lemma and lemma_freq
    read_frequency_data(word_lemma, lemma_freq, word_freq);
    
    //fills unigrams_hbc and word_word_weight_hbc
    read_hbc_data(dictionary, word_word_weight_hbc, unigrams_hbc, file_in, dict_on, word_lemma);
    
    //getting current date
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    file_out = file_out + "_" + to_string(now->tm_mon+1) + "_" + to_string(now->tm_mday) + "_" + to_string(now->tm_year +1900);
   

    //---------------------single-----------------------//
    if(single_){
        cout << "running HBC single" << endl;
        
        //keeps track of the number of outgoing links from each word
        unordered_map< string, int > hbc_single_fan;

        //creates a copy of word_word_weight for hbc single
        unordered_map< pair<string, string > , int, pairHasher> word_word_weight_hbc_single = word_word_weight_hbc;
                
        if(dict_on){
            file_out = file_out + "_hbc_single";
        }
        else{
            file_out = file_out + "_hbc_single_trash";
        }
        

        //writes .soar outputfile
        single_db(word_word_weight_hbc_single, unigrams_hbc, hbc_single_fan, word_freq, file_out, frequencyTime, frequencyScale);
        
        //creates output csv file of RAT item solutions this data contains
        rat_check(word_word_weight_hbc_single, file_out + "_solution.csv");
        
        cout << endl;
    }
    
    //---------------------double-----------------------//
    if(double_){
        cout << "running HBC double" << endl;
        
        //keeps track of the number of outgoing links from each word
        unordered_map< string, int > hbc_double_fan;
        
        //creates a copy of word_word_weight for hbc double
        unordered_map< pair<string, string> , int, pairHasher> word_word_weight_hbc_double = word_word_weight_hbc;
        
        if(dict_on){
            file_out = file_out + "hbc_double";
        }
        else{
            file_out = file_out + "hbc_double_trash";
        }

        //writes .soar outputfile
        double_db(word_word_weight_hbc_double, unigrams_hbc, hbc_double_fan, file_out);
        
        //creates output csv file of RAT item solutions this data contains
        rat_check(word_word_weight_hbc_double, file_out + "_solution.csv");

        cout << endl;
    }
}

void COCA_TG(unordered_set<string> &dictionary){
    unordered_map<string, int> unigrams_COCA_TG;
    unordered_map< pair<string, string> , int, pairHasher> word_word_weight_COCA_TG;
    //maps words to known lemmas
    unordered_map<string, string> word_lemma;
    
    //maps lemmas to their frequency
    unordered_map<string, int> lemma_freq;
    
    //maps words to their frequency
    unordered_map<string, int> word_freq;
    
    //fills word_lemma and lemma_freq
    read_frequency_data(word_lemma, lemma_freq, word_freq);
    
    read_COCA_TG_data(dictionary, word_word_weight_COCA_TG, unigrams_COCA_TG, 600, word_lemma);
    
    unordered_map< string, int> COCA_TG_double_fan;
    double_db(word_word_weight_COCA_TG, unigrams_COCA_TG, COCA_TG_double_fan, "COCA_TG_double");
}

//TODO how to print out bools
/*
void print_params(string dictionary_file, bool single_, bool double_, bool dict_on, string file_in){
    cout << "dictionary: " + string(dict_on) << endl;
    if(dict_on){
        cout << "dictionary file: " + dictionary_file << endl;;
    }
    cout << "single: " + string(single_) << endl;
    cout << "double: " + string(double_) << endl;
    cout << "file in: " + string(file_in) << endl;

}
*/

int main(int argc, char* argv[]){
    
    //parameters needed:  dictionary file || false, double || single, file in name, frequencyTime, freqScale, filename (optional)
    string file_in, file_out, dict_file, file_out_prefix;
    bool dictionary_param = false;
    bool single_param = false;
    bool double_param = false;
    int frequencyTime = 0;
    double frequencyScale = 1;

    string fileName = "";

    unordered_set<string> dictionary;

    //true words.txt true false assoc_17_08_22_18.csv out_test
    if(argc != 6 && argc != 7){
        cout << "Error with input! please input: dictionary file || false, double || single, file in name, frequencyTime, freqScale, filename (optional)" << endl;
        exit(1);
    }

    cout << "starting semantic memory generation..." << endl;

    int index = 1;

    if(string(argv[index++]) != "false"){
        dictionary_param = true;
        dict_file = string(argv[index++]);
        create_dictionary(dictionary, dict_file);
    }

    if(string(argv[index]) == "single"){
        single_param = true;
    }

    else if(string(argv[index]) == "double"){
        double_param = true;
    }
    else{
        cout << "ERROR with double or single" << endl;
        exit(1);
    }
    
    index++;

    file_in = string(argv[index++]);
    
    frequencyTime = atoi(argv[index++]);
    
    frequencyScale = atof(argv[index++]);
    
    if((argc == 7 && dictionary_param == false) || argc == 8){
        fileName = string(argv[index++]);
    }


   // print_params(dict_file, single_param, double_param, dictionary_param, file_in);

    
    //collocation check is not currently being done because the collocation dataset seemed incomplete
    //unordered_map<string, unordered_set<string> > collocations;
    //create_collocations(collocations);

    hbc(dictionary, single_param, double_param, dictionary_param, file_in, frequencyTime, frequencyScale, fileName);
    
}
