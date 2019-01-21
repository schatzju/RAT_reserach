#include "double_db.h"

using namespace std;

bool myfunction(pair<string, int> one, pair<string, int> two){
    return one.second < two.second;
}


void double_db(unordered_map< pair<string, string> , int, pairHasher> &word_word_weight, unordered_map<string, int> &unigrams, unordered_map< string, int> &fan, string name){
    
    //create stream for soar output
    stringstream out;
    out << "smem --add { \n";
    
    vector<pair<string, int>> unigrams_vec;

    for(auto unigram: unigrams){
        unigrams_vec.push_back(unigram);
    }
    
    sort(unigrams_vec.begin(), unigrams_vec.end(), myfunction);
    
    for(int i = 0; i < unigrams_vec.size(); i++){
        out << "\t(<" << unigrams_vec[i].second << "> ^word " << unigrams_vec[i].first << ") \n";
    }
    
    int count_unique = 0;
    
    unordered_map<pair<string, string>, int, pairHasher> copy_www = word_word_weight;
    
    //creating the double connections
    for(auto www_iter : copy_www){

        string word1 = www_iter.first.first;
        string word2 = www_iter.first.second;
        int weight = www_iter.second;
        
        //if word2 word1 weight exists, update the weight of both to be the max
        if(word_word_weight.find(make_pair(word2, word1)) != word_word_weight.end()){
            // found in db
            count_unique++;
            int max_weight = max(word_word_weight[make_pair(word2, word1)], weight);
            
            word_word_weight[make_pair(word2, word1)] = max_weight;
            word_word_weight[make_pair(word1, word2)] = max_weight;
        }
        //otherwise add in a connection between word2 and word1
        else{
            word_word_weight[make_pair(word2, word1)] = weight;
        }
    }
    
    int assoc_count = 0;
    
    for(auto www_iter : word_word_weight){
        string word1 = www_iter.first.first;
        string word2 = www_iter.first.second;
        int weight = www_iter.second;
        assoc_count++;
        out << "\t(<" << unigrams[word1] << "> ^assoc " << "<" << unigrams[word2] << "> (" << weight <<  ".0)) \n";
    }
    
    //creates output csv file of RAT item solutions this data contains
    rat_check(word_word_weight, name + "_solution.csv");
    
    out << "}";
    
    cout << endl << name << endl;
    cout << "Association count: " << assoc_count << endl;
   
    ofstream datFile;
    datFile.open(name + ".soar");
    datFile.write(out.str().c_str(), out.str().length());
}
