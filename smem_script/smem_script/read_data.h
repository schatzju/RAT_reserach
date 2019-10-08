//
//  read_data.hpp
//  smem_script
//
//  Created by Jule Schatz on 4/7/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#ifndef read_data_hpp
#define read_data_hpp

#include <stdio.h>
#include <set>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include "dictionary.h"
#include "RAT_solution_check.h"
#include "util.h"

using namespace std;

//The function fills the word_word_weight map with all rows from the HBC dataset where word1 and
//word2 are found in the dictionary. It fills the unigrams map with every word seen in the valid
//rows and assigns each word a unique identifier.
void read_hbc_data(unordered_set<string> &dictionary, unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, string file_name, bool dict_on, unordered_map<string, int> &word_fan, unordered_map<string, int> &word_assoc,  unordered_map<string, set<string>> &word_to_outgoing, string type);

//The function fills the word_word_weight map with all rows from the pruned 2-grams COCA dataset where
//word1 and word2 are found in the dictionary and any word1 word2 combinations that forms a before seen
//compound word.The weight given to these compound words is decided by the weight_compound input paramater
//It fills the unigrams map with every word seen in the valid rows and assigns each word a unique
//identifier. (Loosely based off of the comRAT-C research)
void read_COCA_TG_data(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, int weight_compound);

//Given a file of three columns "word1, word2, weight", the function fills the word_word_weight map with
//all rows where word1 and word2 are found in the dictionary. It fills the unigrams map with every
//word seen in the valid rows and assigns each word a unique identifier.
void read_data(unordered_set<string> &dictionary, unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, string file_in, bool dict_on, unordered_map<string, int> &word_fan, unordered_map<string, int> &word_assoc, unordered_map<string, set<string>> &word_to_outgoing, string type);

void read_hbc_data_subset(unordered_set<string> &dictionary, unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, bool dict_on, vector<int> subset);

#endif /* read_data_hpp */

