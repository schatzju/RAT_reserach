//
//  write_data.cpp
//  smem_script
//
//  Created by Jule Schatz on 6/24/19.
//  Copyright © 2019 Jule Schatz. All rights reserved.
//

#include "write_data.hpp"
#include <regex>
#include <iomanip>


static void write_unigrams(unordered_map<string, int> &unigrams, stringstream &out){
    for(auto unigram: unigrams){
        out << "\t(@" << unigram.second << " ^word " << unigram.first << ") \n";
    }
    cout << "Word Count: " << unigrams.size() << endl;
}

static void write_connections(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight,unordered_map<string, int> &unigrams, stringstream &out,  unordered_map<string, int> &word_assoc){
    int assoc_count = 0;
    int weight_total = 0;
    
    for(auto www_iter : word_word_weight){
        string word1 = www_iter.first.first;
        string word2 = www_iter.first.second;
        int orig_weight = www_iter.second;
        
        int total_weight = word_assoc[word1];
        
        //NORMALIZE STEP
        double weight = double(orig_weight)/total_weight;
        
        //reversed
//        if( weight == 1){
//            //cout << "\t(@" << unigrams[word1] << " ^assoc " << "@" << unigrams[word2] << " (" << weight <<  ".0)) \n";
//            out << "\t(@" << unigrams[word2] << " ^assoc " << "@" << unigrams[word1] << " (" << weight <<  ".0)) \n";
//        }
//        else{
//            out << "\t(@" << unigrams[word2] << " ^assoc " << "@" << unigrams[word1] << " (" << weight << ")) \n";
//        }
//
//        if(word1 == "high" || word2 == "high"){
//            cout << word1 << ", " << word2 << " : " << weight << endl;
//        }

//        cut cream war
        
        
        //NORMAL
        if( weight == 1){
            //cout << "\t(@" << unigrams[word1] << " ^assoc " << "@" << unigrams[word2] << " (" << weight <<  ".0)) \n";
            out << "\t(@" << unigrams[word1] << " ^assoc " << "@" << unigrams[word2] << " (" << weight <<  ".0)) \n";
        }
        else{
            out << "\t(@" << unigrams[word1] << " ^assoc " << "@" << unigrams[word2] << " (" << weight << ")) \n";
        }
        
        assoc_count++;
        weight_total += weight;
    }
    
    cout << "Association Count: " << assoc_count << endl;
    cout << "Association Sum: " << weight_total << endl;
}

static void create_double_connections(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight,unordered_map<string, int> &unigrams, stringstream &out, unordered_map<string, int> &word_assoc){
    
    unordered_map<pair<string, string>, int, pairHasher> copy_www = word_word_weight;
    
    //creating the double connections
    for(auto www_iter : copy_www){
        
        string word1 = www_iter.first.first;
        string word2 = www_iter.first.second;
        int weight = www_iter.second;
        
        //if word2 word1 weight exists, update the weight of both to be the max
        if(word_word_weight.find(make_pair(word2, word1)) != word_word_weight.end()){
            int word2Weight = word_word_weight[make_pair(word2, word1)];
            int word1Weight = weight;
            int max_weight = 0;
            
            if( word2Weight > word1Weight){
                max_weight = word2Weight;
                word_assoc[word1] = word_assoc[word1] - word1Weight + max_weight;
            }
            
            if( word1Weight > word2Weight){
                max_weight = word1Weight;
                word_assoc[word2] = word_assoc[word2] - word2Weight + max_weight;
            }
            if( word2Weight == word1Weight){
                max_weight = word2Weight;
            }
            
            word_word_weight[make_pair(word2, word1)] = max_weight;
            word_word_weight[make_pair(word1, word2)] = max_weight;
        }
        //otherwise add in a connection between word2 and word1
        else{
            word_word_weight[make_pair(word2, word1)] = weight;
            word_assoc[word2] = word_assoc[word2] + weight;

        }
    }
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

void write_data(bool isDouble, unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, unordered_map< string, int> &fan, string name, unordered_map<string, int> &freq_map, unordered_map<string, int> &word_assoc, int frequencyTime, double frequencyScale){
    
    //create stream for soar output
    stringstream out;
    out << "smem --add { \n";
    
    //(<word> ^word <id_num>)
    write_unigrams(unigrams, out);
    
    if(isDouble){
        //adds two directions to word_word_weight map
        create_double_connections(word_word_weight, unigrams, out, word_assoc);
    }
    
    //(<id_num1> ^assoc <id_num2> (weight.0))
    write_connections(word_word_weight, unigrams, out, word_assoc);
    
    out << "}";
    
    if(frequencyScale != 0){
        write_frequency_data(out, freq_map, unigrams, frequencyTime, frequencyScale);
    }
    
    cout << "writing " + name << endl;
    
    ofstream datFile;
    datFile.open("../smem_soar_databases/soarFiles/" + name + ".soar");
    datFile.write(out.str().c_str(), out.str().length());
    
}





