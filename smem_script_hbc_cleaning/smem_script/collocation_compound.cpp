//
//  collocation.cpp
//  smem_script
//
//  Created by Jule Schatz on 4/6/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#include "collocation_compound.h"
#include "dictionary.h"
using namespace std;


//create collocation map
void create_collocations(unordered_map<string, unordered_set<string> > &collocations_in){
    
    //read in collocation information into dictionary that holds an unordered set
    ifstream coll_file;
    coll_file.open("collocates_60k_b357.txt");
    
    if(!coll_file.is_open()) {
        cout << "Error opening collocates_60k_b357.txt" << endl;
        exit(1);
    }
    
    //reads in intro trash text
    string intro = " ";
    int count = 0;
    while(count < 8){
        coll_file >> intro;
        if(intro == "----"){
            count++;
        }
    }
    
    string word1, word2, trash, id;
    
    string prev_id = "0";
    
    while(coll_file >> id){
        coll_file >> word1 >> trash >> word2 >> trash >> trash >> trash >> trash >> trash;
        
        removeWhitespace(word1);
        removeWhitespace(word2);
        
        if(prev_id != id){
            unordered_set<string> temp;
            collocations_in.emplace(word1, temp);
            prev_id = id;
        }
        collocations_in[word1].emplace(word2);
    }
}

//returns true if word1 word2 is a collocation
bool check_collocate(string word1, string word2, unordered_map<string, unordered_set<string> > &collocations_in){
    auto key = collocations_in.find(word1);
    if(collocations_in.find(word1) != collocations_in.end()){
        if(key->second.find(word2) != key->second.end()){
            return true;
        }
    }
    return false;
}


