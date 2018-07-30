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

//const string database_loc = "new_hbc_double.db";
//const string database_cp_loc = "new_hbc_double_cp.db";
const string db_loc = ".db";
const string db_cp_loc = "_cp.db";
const string c_soar_source_loc = "models/cued_soar_agent/_load.soar";
const string f_soar_source_loc = "models/freeRecall_soar_agent/_load.soar";


void removeWhitespace(std::string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
            str.erase(i, 1);
            i--;
        }
    }
}

void reset_database(string database_loc, string database_cp_loc){
    remove( database_cp_loc.c_str());
     std::ifstream  src(database_loc.c_str(), std::ios::binary);
     std::ofstream  dst(database_cp_loc.c_str(), std::ios::binary);
     dst << src.rdbuf();
}



int main(int argc, char** argv){
	char mode = 'x';
	int num_attempt = -1;
    string soar_source_loc = f_soar_source_loc;
    string database_loc;
	string database_cp_loc;
	string database;

	//optional RAT problem specification
	string rat_prob_file = "raw_144.txt";

	if (argc < 4 |!(argv[1][0]=='f'|argv[1][0]=='c')) {
		cerr << "error! pls specify mode and #attempt: f(ree recall) 1 || c(ued) n || database name" << endl;
		exit(1);
	}
	else {
		mode = argv[1][0];
		num_attempt = atoi(argv[2]);
		database = string(argv[3]);

		if(database.substr(database.length() - 3, 3) == ".db"){
			cout << "WARNING: removing the .db from the database name inputed" << endl;
			database.erase(database.length() - 3, 3);
		}
		database_loc = string(argv[3]) + db_loc;
		database_cp_loc = string(argv[3]) + db_cp_loc;

		if(argc == 5){
			rat_prob_file = string(argv[4]);
		}
	}
   
	if (mode == 'c'){
        num_attempt = 1;
        soar_source_loc = c_soar_source_loc;
    }

    if(mode == 'f') cout << "MODE: f ATTEMPTS: " << to_string(num_attempt) << endl;
    if(mode == 'c') cout << "MODE: c" << endl;

    

	//Read in rat examples ------------------
	
	ifstream fin;
	fin.open(rat_prob_file);

	if (!fin.is_open()) {
		cout << "Error opening " + rat_prob_file << endl;
		exit(1);
	}

	vector< vector<string> > rat_word_data;
	string word1, word2, word3, solution;

	int rat_size = 0;

	while (fin >> word1 >> word2 >> word3 >> solution) {
		rat_size++;
		vector<string> word_tri;

		removeWhitespace(word3);
		
		word_tri.push_back(word1);
		word_tri.push_back(word2);
		word_tri.push_back(word3);
		word_tri.push_back(solution);

		rat_word_data.push_back(word_tri);
	}

	//Used to store all results for creating a combined results file
	vector< vector<unsigned int> > combined_results(rat_size);

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
    
    reset_database(database_loc, database_cp_loc);

    pAgent->LoadProductions(soar_source_loc.c_str());
    pAgent->ExecuteCommandLine(("smem --set path " + database_cp_loc).c_str());
    pAgent->ExecuteCommandLine("smem --set database file");

    //put three words on the input link
    Identifier* pInputLink = pAgent->GetInputLink();
        
    Identifier* max_assoc;
    if (mode == 'f') max_assoc = pAgent->CreateIdWME(pInputLink, "max-attempts");
    if (mode == 'c') max_assoc = pAgent->CreateIdWME(pInputLink, "max_assoc");;
    IntElement* max_num = pAgent->CreateIntWME(max_assoc, "num", num_attempt);

    Identifier* pID_board = pAgent->CreateIdWME(pInputLink, "board");
    Identifier* pID_card1 = pAgent->CreateIdWME(pID_board, "card");
    Identifier* pID_card2 = pAgent->CreateIdWME(pID_board, "card");
    Identifier* pID_card3 = pAgent->CreateIdWME(pID_board, "card");

    StringElement* pID_word1 = pAgent->CreateStringWME(pID_card1, "word", " ");
    StringElement* pID_word2 = pAgent->CreateStringWME(pID_card2, "word", " ");
    StringElement* pID_word3 = pAgent->CreateStringWME(pID_card3, "word", " ");

	for (int j= 0; j < num_attempt; j++) {

		ofstream datFile;
		
		if (mode == 'f') {
			datFile.open("rat_out_freeRecall_" + to_string(num_attempt) + "_" + database + ".csv");
			datFile << "word1,word2,word3,solution,result,attempts,connections,correct" << endl;
		}
		if (mode == 'c') {
			datFile.open("rat_out_cued_" + database + ".csv");
			datFile << "word1,word2,word3,solution,result,connections,correct" << endl;

		}

		//loop through RAT problems  
		for (int i = 0; i < rat_word_data.size(); i++) {

			assert(rat_word_data[i].size() == 4);

			word1 = rat_word_data[i][0];
			word2 = rat_word_data[i][1];
			word3 = rat_word_data[i][2];
			solution = rat_word_data[i][3];

            datFile << word1 << "," << word2 << "," << word3 << "," << solution << ",";

			cout << word1 << " " << word2 << " " << word3 << endl;

			pAgent->Update(pID_word1, word1.c_str());
			pAgent->Update(pID_word2, word2.c_str());
			pAgent->Update(pID_word3, word3.c_str());
           
            if (mode == 'f') pAgent->Update(max_num, num_attempt);
			
			pAgent->Commit();

			int step = 0;
			
			
			//run while there isn't any new output.
			do {
                step++;
                pAgent->RunSelf(1);
                
            } while (!pAgent->Commands() && step < 400);

			if (step == 400) {

				cout << "NA" << endl;
		
				switch (mode) {
				case 'c':
					datFile << "NA,0" << endl;
					break;
				case 'f':
					datFile << "NA,0,0";
		
					combined_results[i].push_back(0);
					cout << "NA" << endl;
					break;
				}
			}
			else {
				Identifier* pCommand = pAgent->GetCommand(0);

				string result = pCommand->GetParameterValue("word");
				string num = pCommand->GetParameterValue("num");

                cout << result << endl;

                removeWhitespace(result);

                string attempts;
                if (mode == 'f') {
                    attempts = pCommand->GetParameterValue("attempts");
                    datFile << result << "," << attempts << "," << num << ",";
                
                    if(result == solution){
                        datFile << '1' << endl;
                        combined_results[i].push_back(1);
                    }
                    else{
                        datFile << '0' << endl;
                        combined_results[i].push_back(0);
                    }
                }

                if (mode == 'c'){
    				datFile << result << "," << num << ",";

    				if (result == solution) {
    					datFile << '1' << endl;
    				}
    				else {
    					datFile << '0' << endl;
    				}
                }
			}

			pAgent->ExecuteCommandLine("init");
			reset_database(database_loc, database_cp_loc);

		}//through 144
		
		if (mode == 'f') reset_database(database_loc, database_cp_loc);
	}
   
   	//creating combined file
	if (mode == 'f') {
		ofstream comFile;
		comFile.open("rat_out_freeRecall_combined_" + database + ".csv");

		for (int i = 0; i < combined_results.size(); i++) {
			for (int k = 0; k < combined_results[i].size() - 1; k++) {
				comFile << combined_results[i][k] << ", ";
			}
			comFile << combined_results[i][combined_results[i].size() - 1] << endl;
		}
	}

    pKernel->Shutdown() ;   // Deletes all agents (unless using a remote connection)
    delete pKernel ;        // Deletes the kernel itself
    
}
