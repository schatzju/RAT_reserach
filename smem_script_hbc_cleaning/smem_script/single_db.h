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

//This function writes the data into a file for soar to read in for loading its semantic memory. It also
//calls RAT_solution_check() to produce a possible solution csv file.
void single_db(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, unordered_map< string, int> &fan, string name);

#endif /* single_db_h */
