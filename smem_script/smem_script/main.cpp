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
#include "write_data.hpp"
#include "dictionary.h"
#include "collocation_compound.h"
#include "RAT_solution_check.h"
#include "read_data.h"
#include "correction.h"
#include "frequency_data.hpp"
#include <cstdlib>  // For srand() and rand()


using namespace std;

unordered_map< pair<string, string> , int, pairHasher> vary_data(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight,unordered_map<string, int> &unigrams_hbc, unordered_map<string, set<string>> &word_to_outgoing){
    
    unordered_map< pair<string, string> , int, pairHasher> new_word_word_weight;
    //loop through words and adjust all outgoing links
    for(auto cur_word : unigrams_hbc){
        vector<pair<string, int>> intervals;
        //get number of outgoing connections
        int total_outgoing = 0;
        
        //loops through all outgoing words from cur_word and adds up total strengths
        for(auto out_word : word_to_outgoing[cur_word.first]){
            int outgoing_weight = word_word_weight[make_pair(cur_word.first, out_word)];
            intervals.push_back(make_pair(out_word, outgoing_weight + total_outgoing));
            total_outgoing += outgoing_weight;
        }
        
        //generate new links based on distribution of old links
        for(int i = 0; i < total_outgoing; i++){
            int rand_num = (rand() % total_outgoing);
            int index = 0;
            for(int k = 0; k < intervals.size(); k++){
                if(intervals[k].second > rand_num){
                    break;
                }
                else{
                    index++;
                }
            }
            
            pair<string, string> w1_w2 = make_pair(cur_word.first, intervals[index].first);
            if(new_word_word_weight.find(w1_w2) == new_word_word_weight.end()){
                new_word_word_weight[w1_w2] = 1;
            }
            else{
                new_word_word_weight[w1_w2] = 1 + new_word_word_weight[w1_w2];
            }
        }
    }
    
    return new_word_word_weight;
}

void generate_populate(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams_hbc, string file_out, unordered_map<string, set<string>> &word_to_outgoing, unordered_map<string, int> &freq_map){
    srand(time(0));
    long past_time = time(0);
    for(int i = 0; i < 500; i++){
        cout << "VARIATION: " << i << endl;
        
        //maps words to their frequency
        unordered_map<string, int> word_freq;
        
        //add varient to data
        unordered_map< pair<string, string> , int, pairHasher> word_word_weight_varient = vary_data(word_word_weight, unigrams_hbc, word_to_outgoing);
        
        //write to output file

        //keeps track of the number of outgoing links from each word
        unordered_map< string, int > hbc_single_fan;
        
        //creates a copy of word_word_weight for hbc single
        unordered_map< pair<string, string > , int, pairHasher> word_word_weight_varient_cp = word_word_weight_varient;
        
        string file_out_temp = file_out + "_varient" + to_string(i);
        
        //maps words to their total outgoing association strengths
        unordered_map<string, int> word_assoc;
        
        //writes .soar outputfile
        write_data(false, word_word_weight_varient_cp, unigrams_hbc, hbc_single_fan, file_out_temp, word_assoc, word_freq);
        
        //creates output csv file of RAT item solutions this data contains
        //rat_check(word_word_weight_hbc_single, file_out + "_solution", word_fan, word_assoc);
        
        cout << "Time to run: " << to_string(time(0) - past_time) << endl;
        past_time = time(0);
        
        cout << endl;
        
        
    }
}


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
    //unordered_map<string, string> word_lemma;

    //maps lemmas to their frequency
    //unordered_map<string, int> lemma_freq;
    
    //maps words to their frequency
    unordered_map<string, int> word_freq;
    
    //maps words to their fan
    unordered_map<string, int> word_fan;
    
    //maps words to their total outgoing association strengths
    unordered_map<string, int> word_assoc;
    
    //word to all outgoing words
    unordered_map<string, set<string>> word_to_outgoing;
    
    //fills word_lemma and lemma_freq
    read_frequency_data(word_freq);
    
    //getting current date
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    file_out = file_out + "_" + to_string(now->tm_mon+1) + "_" + to_string(now->tm_mday) + "_" + to_string(now->tm_year +1900);
   

    //---------------------single-----------------------//
    if(single_){
        cout << "running HBC single" << endl;
        
        //fills unigrams_hbc and word_word_weight_hbc
        read_hbc_data(dictionary, word_word_weight_hbc, unigrams_hbc, file_in, dict_on, word_fan, word_assoc, word_to_outgoing, "single");

        //keeps track of the number of outgoing links from each word
        unordered_map< string, int > hbc_single_fan;

        //creates a copy of word_word_weight for hbc single
        unordered_map< pair<string, string > , int, pairHasher> word_word_weight_hbc_single = word_word_weight_hbc;
                
        if(dict_on){
            file_out = file_out + "_hbc_single_cleaned";
        }
        else{
            file_out = file_out + "_hbc_single_trash";
        }
        

        //writes .soar outputfile
        write_data(false, word_word_weight_hbc_single, unigrams_hbc, hbc_single_fan, file_out,word_freq, word_assoc, frequencyTime, frequencyScale);
    
        //creates output csv file of RAT item solutions this data contains
        rat_check(word_word_weight_hbc_single, file_out + "_solution", word_fan, word_assoc);
        
        cout << endl;
    }
    
    //generate_populate(word_word_weight_hbc, unigrams_hbc, file_out, word_to_outgoing, word_freq);
    
    //---------------------double-----------------------//
    if(double_){
        cout << "running HBC double" << endl;
        
        //fills unigrams_hbc and word_word_weight_hbc
        read_hbc_data(dictionary, word_word_weight_hbc, unigrams_hbc, file_in, dict_on, word_fan, word_assoc, word_to_outgoing, "double");

        
        //keeps track of the number of outgoing links from each word
        unordered_map< string, int > hbc_double_fan;
        
        //creates a copy of word_word_weight for hbc double
        unordered_map< pair<string, string> , int, pairHasher> word_word_weight_hbc_double = word_word_weight_hbc;
        
        if(dict_on){
            file_out = file_out + "_hbc_double_cleaned";
        }
        else{
            file_out = file_out + "_hbc_double_trash";
        }

        //writes .soar outputfile
        write_data(true, word_word_weight_hbc_double, unigrams_hbc, hbc_double_fan, file_out, word_freq, word_assoc);
        
        //creates output csv file of RAT item solutions this data contains
        rat_check(word_word_weight_hbc_double, file_out + "_solution", word_fan, word_assoc);

        cout << endl;
    }
}

void COCA_TG(){
    
    string file_out = "COCA-TG";
    
    //getting current date
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    file_out = file_out + "_" + to_string(now->tm_mon+1) + "_" + to_string(now->tm_mday) + "_" + to_string(now->tm_year +1900);
    
    unordered_map<string, int> unigrams_COCA_TG;
    unordered_map< pair<string, string> , int, pairHasher> word_word_weight_COCA_TG;
    
    //keeps track of the number of outgoing links from each word
    unordered_map< string, int > COCA_TG_fan;
    
    read_COCA_TG_data(word_word_weight_COCA_TG, unigrams_COCA_TG, 600);
    
    //maps words to their frequency
    //CURRENTLY UNUSED
    unordered_map<string, int> word_freq;
    
    //maps words to their total outgoing association strengths
    unordered_map<string, int> word_assoc;
    
    write_data(true, word_word_weight_COCA_TG, unigrams_COCA_TG, COCA_TG_fan, file_out, word_assoc, word_freq);
    
    //maps words to their fan
    unordered_map<string, int> word_fan;
    
    rat_check(word_word_weight_COCA_TG, file_out + "_solution", word_fan, word_assoc);

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
    
    if(argc == 2){
        if(string(argv[1]) == "COCA"){
            COCA_TG();
        }
        else{
            cout << "Error with input please input COCA" << endl;
        }
    }
    else{
        //true words.txt true false assoc_17_08_22_18.csv out_test
        if(argc != 6 && argc != 7){
            cout << "Error with input! please input: dictionary file || false, double || single, file in name, frequencyTime, freqScale, filename (optional)" << endl;
            exit(1);
        }

        cout << "starting semantic memory generation..." << endl;

        int index = 1;

        if(string(argv[index]) != "false"){
            dictionary_param = true;
            dict_file = string(argv[index]);
            create_dictionary(dictionary, dict_file);
        }
        index++;

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
        
        if(argc == 7){
            fileName = string(argv[index++]);
        }


       // print_params(dict_file, single_param, double_param, dictionary_param, file_in);

        
        //collocation check is not currently being done because the collocation dataset seemed incomplete
        //unordered_map<string, unordered_set<string> > collocations;
        //create_collocations(collocations);

        hbc(dictionary, single_param, double_param, dictionary_param, file_in, frequencyTime, frequencyScale, fileName);
    }
}
