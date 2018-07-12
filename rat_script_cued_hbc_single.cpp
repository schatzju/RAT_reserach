#include "../include/sml_Client.h"
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <utility> //pairs
#include <iostream>
#include <sstream> //ostringstream
#include <iomanip>
#include <time.h>
#include <stdio.h> //rename
#include <getopt.h>
#include <sys/stat.h>

using namespace std;
using namespace sml;

const string database_loc = "june_20_2018_hbc_single_trash.db";
const string database_cp_loc = "june_20_2018_hbc_single_trash_cp.db";
const string soar_source_loc = "models/cued_soar_agent/_load.soar";
//const unsigned int start_attempts = 1; //must be higher than 0
//const unsigned int end_attempts = 31; //not inclusive

void removeWhitespace(std::string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
            str.erase(i, 1);
            i--;
        }
    }
}

void reset_database(){
    remove( database_cp_loc.c_str());
     std::ifstream  src(database_loc.c_str(), std::ios::binary);
     std::ofstream  dst(database_cp_loc.c_str(), std::ios::binary);
     dst << src.rdbuf();
}

int main(){
    //Read in 144 rat examples ------------------
    ifstream fin;
    fin.open("raw_144.txt");
        
    if(!fin.is_open()) {
        cout << "Error opening raw_144.txt!" << endl;
        exit(1);
    }

    vector< vector<string> > rat_word_data;

    string word1, word2, word3, solution;

    while(fin >> word1 >> word2 >> word3 >> solution){
        vector<string> word_tri;
        word_tri.push_back(word1);
        word_tri.push_back(word2);
        word_tri.push_back(word3);
        word_tri.push_back(solution);

        rat_word_data.push_back(word_tri);
    }

    //-------------------------------------------

    // Create an instance of the Soar kernel in our process
    Kernel* pKernel = sml::Kernel::CreateKernelInNewThread();
    
    cout << "Created Kernel" << endl;
   
    if (pKernel->HadError())
    {
        cout << pKernel->GetLastErrorDescription() << endl;
        return -1;
    }
    
    Agent* pAgent = pKernel->CreateAgent("rat_test");
    
    cout << "Initalized Agent" << endl;
    if (pKernel->HadError())
    {
        cout << "No Agent Actually Gotten" << endl;
        cout << pKernel->GetLastErrorDescription() << endl;
        return -1;
    }
    
    reset_database();

    pAgent->LoadProductions(soar_source_loc.c_str());
    pAgent->ExecuteCommandLine(("smem --set path " + database_cp_loc).c_str());
    pAgent->ExecuteCommandLine("smem --set database file");

    //put "three words on the input link"
    Identifier* pInputLink = pAgent->GetInputLink();

    Identifier* max_assoc = pAgent->CreateIdWME(pInputLink, "max_assoc");
    IntElement* max_num = pAgent->CreateIntWME(max_assoc, "num", 3);

    Identifier* pID_board = pAgent->CreateIdWME(pInputLink, "board");
    Identifier* pID_card1 = pAgent->CreateIdWME(pID_board, "card");
    Identifier* pID_card2 = pAgent->CreateIdWME(pID_board, "card");
    Identifier* pID_card3 = pAgent->CreateIdWME(pID_board, "card");

    //first word
    StringElement* pID_word1 = pAgent->CreateStringWME(pID_card1, "word", " ");
    StringElement* pID_word2 = pAgent->CreateStringWME(pID_card2, "word", " ");
    StringElement* pID_word3 = pAgent->CreateStringWME(pID_card3, "word", " ");

    
    ofstream datFile;
    datFile.open("rat_out_del_" + database_loc + ".csv");

    //loop through 144 RAT examples  
    for(int i = 0; i < rat_word_data.size(); i++){

        assert(rat_word_data[i].size() == 4);

        word1 = rat_word_data[i][0];
        word2 = rat_word_data[i][1];
        word3 = rat_word_data[i][2];
        solution = rat_word_data[i][3];

        cout << word1 << " " << word2 << " " << word3 << endl;

        removeWhitespace(word3);

            pAgent->Update(pID_word1, word1.c_str()); 
            pAgent->Update(pID_word2, word2.c_str()); 
            pAgent->Update(pID_word3, word3.c_str()); 
            pAgent->Commit();
        
        int step = 0;

            do{
                step++;
                pAgent->RunSelf(1);

            } while( !pAgent->Commands() && step < 400);//while there isn't any new output.

        if(step == 400){
            datFile << "NA" << "," << "NA" << "," << 0 << endl;
        }
        else{
            Identifier* pCommand = pAgent->GetCommand(0) ;
            
            string result = pCommand->GetParameterValue("word") ;
            removeWhitespace(result);
            string num = pCommand->GetParameterValue("num") ;
            
            cout << result << endl;
            
            removeWhitespace(solution);
            removeWhitespace(result);
            
            
            datFile << result << "," << num << ",";
            
            if(result == solution){
                datFile << '1' << endl;
            }
            else{
                datFile << '0' << endl;
            }
        }
        
        pAgent->ExecuteCommandLine("init");
        reset_database();

    }//end of attempts number
    
    pKernel->Shutdown() ;   // Deletes all agents (unless using a remote connection)
    delete pKernel ;        // Deletes the kernel itself
    
}
