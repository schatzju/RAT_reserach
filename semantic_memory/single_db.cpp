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

static void write_unigrams(unordered_map<string, int> &unigrams, stringstream &out){
    for(auto unigram: unigrams){
        out << "\t(<" << unigram.second << "> ^word " << unigram.first << ") \n";
    }
    cout << "Word Count: " << unigrams.size() << endl;
}

static void write_connections(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight,unordered_map<string, int> &unigrams, stringstream &out){
    int assoc_count = 0;

    for(auto www_iter : word_word_weight){
        string word1 = www_iter.first.first;
        string word2 = www_iter.first.second;
        int weight = www_iter.second;
        
        assoc_count++;

        out << "\t(<" << unigrams[word1] << "> ^assoc " << "<" << unigrams[word2] << "> (" << weight <<  ".0)) \n";    
    }

    cout << "Association Count: " << assoc_count << endl;
 }

void single_db(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, unordered_map< string, int> &fan, string name){
  
    //create stream for soar output
    stringstream out;
    out << "smem --add { \n";
    
    //(<word> ^word <id_num>)
    write_unigrams(unigrams, out);

    //(<id_num1> ^assoc <id_num2> (weight.0))
    write_connections(word_word_weight, unigrams, out);
    
    out << "}";
    
    cout << "writing " + name << endl;
    
    ofstream datFile;
    datFile.open(name + ".soar");
    datFile.write(out.str().c_str(), out.str().length());
}
