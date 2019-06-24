//
//  write_data.hpp
//  smem_script
//
//  Created by Jule Schatz on 6/24/19.
//  Copyright © 2019 Jule Schatz. All rights reserved.
//

#ifndef write_data_hpp
#define write_data_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include "util.h"

using namespace std;

//This function writes the data into a file for soar to read in for loading its semantic memory with frequency data.
void write_data(bool isSingle, unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, unordered_map< string, int> &fan, string name, unordered_map<string, int> &freq_map, int frequencyTime, double frequencyScale);


#endif /* write_data_hpp */
