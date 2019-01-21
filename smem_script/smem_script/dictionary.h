//
//  dictionary.h
//  smem_script
//
//  Created by Jule Schatz on 11/6/17.
//  Copyright © 2017 Jule Schatz. All rights reserved.
//
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include <cstdlib>
#include <string>
#include "util.h"


using namespace std;
#ifndef dictionary_h
#define dictionary_h

void create_dictionary(unordered_set<string> &dictionary, string file_in);
#endif /* dictionary_h */
