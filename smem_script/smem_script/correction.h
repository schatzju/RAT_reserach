//
//  correction.hpp
//  smem_xcode
//
//  Created by Jule Schatz on 8/14/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#ifndef correction_hpp
#define correction_hpp
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
#include "dictionary.h"
#include "collocation_compound.h"
#include "RAT_solution_check.h"
#include "read_data.h"
#include <set>

using namespace std;
#include <stdio.h>
void correcting(set< pair<int, pair<string, string> >, int_pair_compare> &word_word_weight);

#endif /* correction_hpp */
