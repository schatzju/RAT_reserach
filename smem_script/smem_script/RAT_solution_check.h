//
//  RAT_solution_check.hpp
//  smem_script
//
//  Created by Jule Schatz on 4/6/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#ifndef RAT_solution_check_hpp
#define RAT_solution_check_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include "dictionary.h"
#include "util.h"

using namespace std;

struct pairHasher;

//creates a csv file with the exact rat items word_word_weight has the solution to
//checks that word--weight-->solution exists for all three words
void rat_check(unordered_map< pair<string, string> , int, pairHasher> & word_word_weight, string out_file_name);

#endif /* RAT_solution_check_hpp */
