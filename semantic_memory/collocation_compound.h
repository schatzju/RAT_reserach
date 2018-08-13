//
//  collocation.hpp
//  smem_script
//
//  Created by Jule Schatz on 4/6/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#ifndef collocation_hpp
#define collocation_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>

using namespace std;
//-----------This file isn't currently being used---------------//


//returns true if word1word2 is a new compound word
bool check_compound(string word1, string word2, unordered_set<string> &dictionary);

//create collocation map
void create_collocations(unordered_map<string, unordered_set<string> > &collocations_in);

//returns true if word1 word2 is a collocation
bool check_collocate(string word1, string word2, unordered_map<string, unordered_set<string> > &collocations_in);

#endif /* collocation_hpp */


