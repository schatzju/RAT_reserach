//
//  read_data.cpp
//  smem_script
//
//  Created by Jule Schatz on 4/7/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#include <set>
#include "read_data.h"
#include "correction.h"


//string const FILE_NAME = "assoc_17_08_22_18.csv";

void read_hbc_data(unordered_set<string> &dictionary, unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, string file_name, bool dict_on){
    
    read_data(dictionary, word_word_weight, unigrams, file_name, dict_on);
}

void read_COCA_TG_data(unordered_set<string> &dictionary, unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, int weight_compound){
    
    read_data(dictionary, word_word_weight, unigrams, "ngrams.txt", false);
    
    int compound_int = 0;
    //add compound word associations
    for(auto it: unigrams){
        string word1 = it.first;

        for(auto it2: unigrams){
            string word2 = it2.first;

            if(word1.size() > 2 && word2.size() > 2){
                if(check_compound_unigrams(word1, word2, unigrams)){
                    compound_int++;
                    //if word1 word2 weight exists, update the weight
                    if(word_word_weight.find(make_pair(word1, word2)) != word_word_weight.end()){
                        //if it found it in the map
                        word_word_weight[make_pair(word1, word2)] += weight_compound;
                    }
                    else{
                        word_word_weight[make_pair(word1, word2)] = weight_compound;
                    }
                }
                if(check_compound_unigrams(word2, word1, unigrams)){
                    compound_int++;
                    if(word_word_weight.find(make_pair(word2, word1)) != word_word_weight.end()){
                        //if it found it in the map
                        word_word_weight[make_pair(word2, word1)] += weight_compound;
                    }
                    else{
                        word_word_weight[make_pair(word2, word1)] = weight_compound;
                    }
                }
            }
        }
    }
}

void read_data(unordered_set<string> &dictionary, unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, string file_in, bool dict_on){
    
    cout << "reading in " << file_in << endl;

    //read in raw data
    ifstream file;
    file.open(file_in);
    
    set< pair<int, pair<string, string> >, int_pair_compare> flagged_word_word_weight;
    
    //removing column titles at top of csv file
    string column_title = "";
    getline(file, column_title, ',');
    getline(file, column_title, ',');
    getline(file, column_title);
    
    string word1;
    string word2;
    string weight;
    
    //unique ID for each node to be added into soar's SMEM
    int count = 0;
    
    //number of associations the dataset has
    int count_assoc = 0;
    
    while(getline(file, word1, ',')){
        getline(file, word2, ',');
        getline(file, weight);
        
        //turns words to all lowercase
        transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
        transform(word2.begin(), word2.end(), word2.begin(), ::tolower);

        //this prunes out items with multiple words
        //if words are made of only letters (no spaces, characters, or numbers)
        if(std::regex_match(word1, std::regex("^[A-Za-z]+$")) && std::regex_match(word2, std::regex("^[A-Za-z]+$"))){
            
            //if both words are in the dictionary
            if(dict_on == false || (dictionary.find(word1) != dictionary.end() && dictionary.find(word2) != dictionary.end())){
                
                
                //adds word1 to unigrams if it isn't already there and gives it a unique identifier
                if(unigrams.find(word1) == unigrams.end()){
                    unigrams.emplace(word1, count);
                    count++;
                }
                
                //adds word2 to unigrams if it isn't already there and gives it a unique identifier
                if(unigrams.find(word2) == unigrams.end()){
                    unigrams.emplace(word2, count);
                    count++;
                }
                
                //stores association between word1, word2 with weight
                if(word_word_weight.find(make_pair(word1, word2)) == word_word_weight.end()){
                    word_word_weight[make_pair(word1, word2)] = stoi(weight);
                }
                else{
                    cout << "multiple instances of word1 word 2, " + word1 + " " + word2;
                }
                count_assoc++;

            }//dict if
        }//letters if
    }//file loop
}

/*
void read_hbc_data_subset(unordered_set<string> &dictionary, unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, bool dict_on, vector<int> subset){
    
    read_data(dictionary, word_word_weight, unigrams, FILE_NAME, dict_on);
    
    unigrams.clear();
    
    ifstream inFile;
    inFile.open("raw_144.txt");
    
    ofstream outFile;
    outFile.open("raw_144_sub.txt");
    
    string word1, word2, word3, solution;
    
    int count = 1;
    
    int unique_id = 0;
    
    while(inFile >> word1 >> word2 >> word3 >> solution){
        if(find_vect(subset, count)){
            outFile << word1 << " " << word2 << " " << word3 << " " << solution << endl;
            unigrams[word1] = unique_id++;
            unigrams[word2] = unique_id++;
            unigrams[word3] = unique_id++;
            unigrams[solution] = unique_id++;
        }
        count++;
    }
}
*/
