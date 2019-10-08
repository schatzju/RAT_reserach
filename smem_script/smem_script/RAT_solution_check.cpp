//
//  RAT_solution_check.cpp
//  smem_script
//
//  Created by Jule Schatz on 4/6/18.
//  Copyright © 2018 Jule Schatz. All rights reserved.
//
#include "RAT_solution_check.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include "util.h"

bool in_map(string word1, string solution, unordered_map< pair<string, string> , int, pairHasher> & word_word_weight){
    
    pair<string, string> oneway(word1, solution);
    
    auto it1 = word_word_weight.find(oneway);
    
    if(it1 != word_word_weight.end()){
        return true;
    }
    return false;
}

void func(){
}

void rat_check(unordered_map< pair<string, string> , int, pairHasher> & word_word_weight, string out_file_name, unordered_map<string, int> &word_fan, unordered_map<string, int> &word_assoc){
    
   
    
    ofstream outFileAny;
    outFileAny.open("solution_files/" + out_file_name + ".csv");
    outFileAny << "id,word1,word2,word3,forward,backward,both,either" << endl;
    
    ofstream outFanAssoc;
    outFanAssoc.open("solution_files/" + out_file_name + "_fan_assocBias.csv");
    outFanAssoc << "id,word,fan,assocNormalized" << endl;
    
    ofstream outFanAssocAv;
    outFanAssocAv.open("solution_files/" + out_file_name + "_fan_assoc_averaged.csv");
    outFanAssocAv << "id,fanAveraged,assocBias" << endl;
    
    ifstream inFile;
    inFile.open("raw_144.txt");
    
    ofstream outFileEither;
    outFileEither.open("solution_files/" + out_file_name + "_subRatEither.csv");
    
    ofstream outFileForward;
    outFileForward.open("solution_files/" + out_file_name + "_forwardLinks.csv");
    outFileForward << "id,word1,word2,word3,solution,result,correct" << endl;
    
    ofstream outFileBackward;
    outFileBackward.open("solution_files/" + out_file_name + "_backwardlinks.csv");
    outFileBackward << "id,word1,word2,word3,solution,result,correct" << endl;
    
    string word1, word2, word3, solution;
    int id = 1;
    
    //read in assoc_connect
    ifstream inFileAssoc;
    inFileAssoc.open("assoc_check.txt");
    int idDB = 0;
    inFileAssoc >> idDB;
    
    ofstream outFileDB;
    outFileDB.open("solution_files/" + out_file_name + "_specificCorrectLinks.csv");
    outFileDB << "id,word1,word2,word3,solution,result,connections,correct" << endl;

    ofstream outFileDB2;
    outFileDB2.open("solution_files/" + out_file_name + "_anyCorrectLinks.csv");
    outFileDB2 << "id,word1,word2,word3,solution,result,connections,correct" << endl;

    while(inFile >> word1 >> word2 >> word3 >> solution){
        outFileAny << id << "," << word1 << "," << word2 << "," << word3 << ",";
        outFileDB << id << "," << word1 << "," << word2 << "," << word3 << ",solution,result,";
        outFileDB2 << id << "," << word1 << "," << word2 << "," << word3 << ",solution,result,";
        
        outFileForward << id << "," << word1 << "," << word2 << "," << word3 << ",solution,result,";
        outFileBackward << id << "," << word1 << "," << word2 << "," << word3 << ",solution,result,";

        
        bool forward = false;
        bool backward = false;
        
        //CHECK DB CORRECTNESS
        if(idDB == id){
            string wordA = " ";
            string wordB = " ";
            int correctLinkCount = 0;
            int backwardLinkCount = 0;
            for(int i = 0; i < 3; i++){
                inFileAssoc >> wordA >> wordB;
                if(id != 144 || i !=2){
                    inFileAssoc >> idDB;
                }
                if(in_map(wordA, wordB, word_word_weight)){
                    correctLinkCount++;
                }else{
                    cout << "NOT " << id << ": "<<  wordA << ", " << wordB << endl;
                    if(in_map(wordB, wordA, word_word_weight)){
                        backwardLinkCount++;
                    }
                }
            }
            outFileDB << correctLinkCount << ",";
            outFileDB2 << correctLinkCount << ",";

            if(correctLinkCount == 3){
                outFileDB << 1 << endl;
                outFileDB2 << 1 << endl;
            }
            else{
                outFileDB << 0 << endl;
                if(correctLinkCount+backwardLinkCount == 3){
                    outFileDB2 << 1 << endl;
                }
                else{
                    outFileDB2 << 0 << endl;
                }
            }
            
        }
        else{
            outFileDB << "3," << 1 << endl;
            outFileDB2 << "3," << 1 << endl;
        }
        
       
        //CHECKS FOR FORWARD LINK prompt --> solution
        if(in_map(word1, solution, word_word_weight) && in_map(word2, solution, word_word_weight) && in_map(word3, solution, word_word_weight)){
            outFileAny << "1,";
            outFileForward << "1" << endl;
            forward = true;
            
            //double normalizedAssocWord1 = double(word_word_weight[make_pair(word1, solution)])/double(word_assoc[word1]);
            double assocRatio1 = double(word_word_weight[make_pair(word1, solution)])/double(word_assoc[word1]) - (1.0/double(word_fan[word1]));
    
            outFanAssoc << id << "," << word1 << "," << word_fan[word1] << "," << assocRatio1 << endl;
            
            //double normalizedAssocWord2 = double(word_word_weight[make_pair(word2, solution)])/double(word_assoc[word2]);
            double assocRatio2 = double(word_word_weight[make_pair(word2, solution)])/double(word_assoc[word2]) - (1.0/double(word_fan[word2]));
            outFanAssoc << id << "," << word2 << "," << word_fan[word2] << "," << assocRatio2 << endl;
            
            //double normalizedAssocWord3 = double(word_word_weight[make_pair(word3, solution)])/double(word_assoc[word3]);
            double assocRatio3 = double(word_word_weight[make_pair(word3, solution)])/double(word_assoc[word3]) - (1.0/double(word_fan[word3]));
            outFanAssoc << id << "," << word3 << "," << word_fan[word3] << "," << assocRatio3 << endl;
            
            outFanAssocAv << id << "," << (word_fan[word1]+word_fan[word2]+word_fan[word3])/(3.0) << "," << (assocRatio1+assocRatio2+assocRatio3)/(3.0) << endl;
        }
        else{
            outFileForward << "0" << endl;
            outFileAny << "0,";
        }
        
        //CHECK BACKWARD Link
        if(in_map(solution,word1, word_word_weight) && in_map(solution,word2, word_word_weight) && in_map(solution, word3, word_word_weight)){
            outFileAny << "1,";
            backward = true;
            outFileBackward << "1" << endl;
        }
        else{
            outFileAny << "0,";
            outFileBackward << "0" << endl;
        }
        
        if(forward && backward){
            outFileAny << "1,";
        }
        else{
            outFileAny << "0,";
        }
        if(forward || backward){
            outFileAny << "1";
            outFileEither << word1 << " " << word2 << " " << word3 << " " << solution << endl;
        }
        else{
            outFileAny << "0";
        }
        
        id++;
        outFileAny << endl;
    }
    
}
