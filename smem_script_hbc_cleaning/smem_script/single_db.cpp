#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include "dictionary.h"
#include "RAT_solution_check.h"
#include "single_db.h"

using namespace std;
// unordered_map< string, int> &nodeCounts,

void single_db(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, unordered_map< string, int> &fan, string name){
  
    //create stream for soar output
    stringstream out;
    out << "smem --add { \n";
    
    for(auto unigram: unigrams){
        out << "\t(<" << unigram.second << "> ^word " << unigram.first << ") \n";
    }
    
    unordered_map<string, int> unigrams_orig = unigrams;
    unordered_map< pair<string, string> , int, pairHasher> word_word_weight_sub;
    int assoc_count = 0;
    
    for(auto www_iter : word_word_weight){
        string word1 = www_iter.first.first;
        string word2 = www_iter.first.second;
        int weight = www_iter.second;
        
        if(unigrams_orig.find(word1) != unigrams_orig.end() || unigrams_orig.find(word2) != unigrams_orig.end()){
            
            if(unigrams.find(word1) == unigrams.end()){
                int size = (int)unigrams.size();
                unigrams[word1] = size;
                out << "\t(<" << size << "> ^word " << word1 << ") \n";
            }
            if(unigrams.find(word2) == unigrams.end()){
                int size = (int)unigrams.size();
                unigrams[word2] = size;
                out << "\t(<" << size << "> ^word " << word2 << ") \n";
            }
        
            assoc_count++;
            word_word_weight_sub[pair<string,string>(word1, word2)] = weight;
            out << "\t(<" << unigrams[word1] << "> ^assoc " << "<" << unigrams[word2] << "> (" << weight <<  ".0)) \n";
        }
        
    }
    cout << "word count: " << unigrams.size();

    
    //creates output csv file of RAT item solutions this data contains
    rat_check(word_word_weight_sub, name + "_solution.csv");
    
    out << "}";
    
    cout << name << endl;
    cout << "Association count: " << assoc_count << endl;
    
    ofstream datFile;
    datFile.open(name + ".soar");
    datFile.write(out.str().c_str(), out.str().length());
}
