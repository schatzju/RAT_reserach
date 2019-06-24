//
//  HBC_sinlge.h
//  smem_script
//
//  Created by Jule Schatz on 4/6/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#ifndef single_db_h
#define single_db_h

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include "dictionary.h"
#include "collocation_compound.h"
#include "RAT_solution_check.h"

using namespace std;

void write_unigrams(unordered_map<string, int> &unigrams, stringstream &out);

//This function writes the data into a file for soar to read in for loading its semantic memory. It also
void single_db(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, unordered_map< string, int> &fan,unordered_map<string, int> &freq_map, string name, int frequencyTime, double frequencyScale = 1.0);

#endif /* single_db_h */
