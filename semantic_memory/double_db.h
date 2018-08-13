//
//  HBC_double.h
//  smem_script
//
//  Created by Jule Schatz on 4/6/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#ifndef double_db_h
#define double_db_h

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include <cstdlib>
#include <string>
#include "dictionary.h"
#include <queue>
#include <vector>
#include "RAT_solution_check.h"

using namespace std;

//This function edits word_word_weight to have association that go both ways for every entry. It
//then writes the data into a file for soar to read in for loading its semantic memory. It also
//calls RAT_solution_check() to produce a possible solution csv file.
void double_db(unordered_map< pair<string, string>, int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, unordered_map< string, int> &fan, string name);


#endif /* double_db_h */
