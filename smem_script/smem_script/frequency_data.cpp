//
//  frequency_data.cpp
//  
//
//  Created by Jule Schatz on 1/23/19.
//

#include "frequency_data.hpp"

void read_frequency_data(unordered_map<string, int> &freq_map){

    
    //columns seperated by tab. ID w1 l1 freq
    
    ifstream file;
    file.open("b1416.txt");
    
    if(!file.is_open()) {
        cout << "Error opening b1416.txt!" << endl;
        exit(1);
    }

    
    //Lemma - word forms
    //string - set of words
    
    string temp, word, lemma, freq;
    //removing column titles at top of csv file
    getline(file, temp);
    getline(file, temp, '\n');
    getline(file, temp, '\n');


    while(getline(file, temp, '\t')){
        getline(file, word, '\t');
        getline(file, lemma, '\t');
        
        getline(file, temp, '\t');
        getline(file, temp, '\t');
        getline(file, temp, '\t');
        
        getline(file, freq, '\t');
        getline(file, temp);
        
        //word_lemma_map[word] = lemma;
        
        freq_map[word] = stoi(freq);
        
        //if(lemma_freq_map.find(lemma) != lemma_freq_map.end()){
         //   lemma_freq_map[lemma] =  lemma_freq_map[lemma] + stoi(freq);
        //}
       // else{
        //    lemma_freq_map[lemma] = stoi(freq);
        //}
    }
}
