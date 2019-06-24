#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <unordered_set>
#include <cstdlib>
#include <string>
#include <cassert>


using namespace std;

/*
int main(){
    
    unordered_set<string> tags_found;
    
    vector< pair<string, string> > collocates;
    
    vector< int> freq;
    
    unordered_set<string> accept_pos( { "fu", "fw", "jj", "nd1", "nn", "nn1", "nn2", "ra", "rex", "rr", "rt", "vb0", "vvg", "vvn", "nnu", "nnu1", "nnu2"} );
    
    ifstream wordFile;
    wordFile.open("w2c.txt");
    
    if(!wordFile.is_open()) {
        cout << "Error opening w2c.txt!" << endl;
        exit(1);
    }

    string num, word1, word2, tag1, tag2;
    
    while(wordFile >> num >> word1 >> word2 >> tag1 >> tag2){
        
        
        if(isdigit(tag1[tag1.length()-1]) && isdigit(tag1[tag1.length()-2])){
            tag1.erase(tag1.end()-2, tag1.end());
        }
        if(isdigit(tag2[tag2.length()-1]) && isdigit(tag2[tag2.length()-2])){
            tag2.erase(tag2.end()-2, tag2.end());
        }
        
        if(accept_pos.find(tag1) != accept_pos.end() && accept_pos.find(tag2) != accept_pos.end()){
            
            if(word1.length() > 2 && word2.length() > 2){
                if(word1 != "ing" && word2 != "ing"){
                    pair<string, string> word_pair ({word1,  word2});
                    collocates.push_back(word_pair);
                    freq.push_back(stoi(num));        
                }
            }
        }
        else{
            if(accept_pos.find(tag1) != accept_pos.end()){
                if(tags_found.find(tag2) == tags_found.end()){
                    tags_found.emplace(tag2);
                }
            }
            else if(accept_pos.find(tag2) != accept_pos.end()){
                if(tags_found.find(tag1) == tags_found.end()){
                    tags_found.emplace(tag1);
                }
            }
            else{
                if(tags_found.find(tag2) == tags_found.end()){
                    tags_found.emplace(tag2);
                }
                if(tags_found.find(tag1) == tags_found.end()){
                    tags_found.emplace(tag1);
                }


            }
            
        }
    }
    
    ofstream outFile;
    outFile.open("ngrams.txt");
    
    cout << collocates.size() << endl;
    
    assert(collocates.size() == freq.size() );
    
    outFile << "word1,word2,num" << endl;
    
    for(int i = 0; i < collocates.size(); i++){
        outFile << collocates[i].first << "," << collocates[i].second << "," << freq[i] << endl;
    }
    
    for(auto it: tags_found){
        cout << it << endl;
    }
    
}
*/
