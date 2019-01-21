//
//  correction.cpp
//  smem_xcode
//
//  Created by Jule Schatz on 8/14/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//

#include "correction.h"
#include <set>

#include <iostream>
#include <ios>
#include <vector>
#include <numeric>
#include <chrono>
#include "time.h"


void correcting(set< pair<int, pair<string, string> >, int_pair_compare>&word_word_weight){
    //anything that the dictionary flags, go through in order by biggest word_word_weight.
    //creates txt file of word word weight pairs to remove.
    
    //add stuff to be corrected and to be removed
    //l = leave it in
    //c = to correct, add to correct outfile
    //c1 = correct word 1
    //c2 = correct word 2
    //r1 = remove first word
    //r2 = remove second word
    //n = next
    std::string s = date::format("%F %T", std::chrono::system_clock::now());

    ofstream toCorrect;
    toCorrect.open("toCorrect.txt",  std::ios_base::app);
    
    ofstream toCorrectWord;
    toCorrectWord.open("toCorrectWords.txt",  std::ios_base::app);
    
    ofstream leave;
    leave.open("toAdd.txt", std::ios_base::app);
    
    ofstream toRemove;
    toRemove.open("toRemove.txt", std::ios_base::app);
    
    for(auto www_iter : word_word_weight){
        
        string command = "";
        
        cout << www_iter.second.first << " " << www_iter.second.second << " " << www_iter.first << endl;
        
        while(cin >> command){
            if(command == "n"){
                break;
            }
            else if(command == "l"){
                leave << www_iter.second.first << endl << www_iter.second.second << endl;
            }
            else if(command == "c"){
                toCorrect << www_iter.second.first << " " << www_iter.second.second << " " << www_iter.first << " | " << www_iter.second.first << " " << www_iter.second.second << " " << www_iter.first << endl;
            }
            else if(command == "c1"){
                toCorrectWord << www_iter.second.first << " | " << www_iter.second.first << endl;
            }
            else if(command == "c2"){
                toCorrectWord << www_iter.second.second << " | " << www_iter.second.second << endl;
            }
            else if(command == "r1"){
                toRemove << www_iter.second.first << endl;
            }
            else if(command == "r2"){
                toRemove << www_iter.second.second << endl;
            }
            else if(command.size() > 0){
                cout << "Error!" << endl;
            }
        }
    }

}
