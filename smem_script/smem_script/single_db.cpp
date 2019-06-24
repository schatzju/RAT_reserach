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
#include "filters.h"
#include <iomanip>
#include <iostream>

using namespace std;
// unordered_map< string, int> &nodeCounts,

void write_unigrams(unordered_map<string, int> &unigrams, stringstream &out){
    for(auto unigram: unigrams){
        out << "\t(@" << unigram.second << " ^word " << unigram.first << ") \n";
    }
    cout << "Word Count: " << unigrams.size() << endl;
}

template <class T>
static void write_connections(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight,unordered_map<string, int> &unigrams, stringstream &out, T filter){
    int assoc_count = 0;

    for(auto www_iter : word_word_weight){
        string word1 = www_iter.first.first;
        string word2 = www_iter.first.second;
        int weight = www_iter.second;
    
        
        if(filter(weight)){
            assoc_count++;
            out << "\t(@" << unigrams[word1] << " ^assoc " << "@" << unigrams[word2] << " (" << weight <<  ".0)) \n";
        }
    }

    cout << "Association Count: " << assoc_count << endl;
 }

static void write_frequency_data(stringstream &out, unordered_map<string, int> &freq_map, unordered_map<string, int> &unigrams, int frequencyTime, double frequencyScale){
    
    int count = 0;
    
    double biggest = 0;
    double smallest = 100000;
    
    out << "\nsmem --bla-init " + to_string(frequencyTime) + " {";
    
    for( auto fm_iter : freq_map){
        
        if(unigrams.find(fm_iter.first) != unigrams.end()){
            
            double scaled = fm_iter.second*frequencyScale;
            
            count++;
            out << "(@";
            
            out << unigrams[fm_iter.first];
            
            out << " ";
            
            if(fm_iter.second < 0){
                cout << "NOOO" << endl;
            }
            
            if(scaled > biggest){
                biggest = scaled;
                
            }
            if(scaled < smallest){
                smallest = scaled;
                
            }
            out << std::fixed << scaled << setprecision(3);
            
            out << ")";
        }
    }
    cout << "Frequency added for " << count << " words" <<endl;
    out << "}";
    
    cout << "Biggest Frequency: " << std::fixed << biggest << setprecision(3) << endl;
    cout << "Smallest Frequency: " << std::fixed << smallest << setprecision(3) << endl;

    
}

void single_db(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, unordered_map< string, int> &fan,unordered_map<string, int> &freq_map, string name, int frequencyTime, double frequencyScale){
  
    //create stream for soar output
    stringstream out;
    out << "smem --add { \n";
    
    //(<word> ^word <id_num>)
    write_unigrams(unigrams, out);

    //(<id_num1> ^assoc <id_num2> (weight.0))
    
    Thresh filterThresh(0);
    
    write_connections(word_word_weight, unigrams, out, filterThresh);
    
    out << "}";
    
    if(frequencyScale != 0){
        write_frequency_data(out, freq_map, unigrams, frequencyTime, frequencyScale);
    }
    
    cout << "writing " + name << endl;
    
    ofstream datFile;
    datFile.open("../smem_soar_databases/soarFiles/" + name + ".soar");
    datFile.write(out.str().c_str(), out.str().length());
}
