#include "sml_Client.h"
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
#include <chrono>       // std::chrono::system_clock


using namespace std;
using namespace sml;

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

bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void reset_database(string database_loc, string database_cp_loc){
	cout << database_loc << endl;
    remove( database_cp_loc.c_str());
     std::ifstream  src(database_loc.c_str(), std::ios::binary);
     std::ofstream  dst(database_cp_loc.c_str(), std::ios::binary);
     dst << src.rdbuf();
}



int main(int argc, char** argv){
	char mode = 'x';
	int num_attempt_start = 0;
	int num_attempt_end = 0;
    string soar_source_loc = f_soar_source_loc;
    string database_loc;
	string database_cp_loc;
	string database;
	string output_path;
	char* soar_settings;
	bool rand = false;

	//optional RAT problem specification
	string rat_prob_file = "raw_144.txt";

	if (argc < 3 ||!(argv[1][0]=='f'|| argv[1][0]=='c')) {
		cerr << "error! pls specify mode and #attempts start and #attempts end: [f(ree recall) n n+ || c(ued)] <randomize RAT items T or F> <database name>  <path for output> <additional smem commands> <rat_file(optional)> " << endl;
		exit(1);
	}

	mode = argv[1][0];

	if(argv[2][0] == 'T'){
		rand = true;
	}

	if(mode == 'f'){

		if(argc < 6){
			cerr << "error! for the free recall agent please specify at least #attempt_start #attempt_end database_name output_path" << endl;
			exit(1);
		}

		num_attempt_start = atoi(argv[3]);
		num_attempt_end = atoi(argv[4]);

		database = string(argv[5]);
        output_path = string(argv[6]);


        if(argc >= 8){
       		soar_settings = argv[7];
        }

        if(argc == 9){
       		rat_prob_file = string(argv[8]);
        }

        cout << "MODE: f ATTEMPTS: " << to_string(num_attempt_end) << endl;
	}
		
	if(mode == 'c'){
		soar_source_loc = c_soar_source_loc;

		num_attempt_start = 1;
		num_attempt_end = 1;

		database = string(argv[3]);
        output_path = string(argv[4]);

        if(argc >= 6){
       		soar_settings = argv[5];
        }

        if(argc == 7){
       		rat_prob_file = string(argv[6]);
        }

        cout << "MODE: c" << endl;
	}


	if(database.substr(database.length() - 3, 3) == ".db"){
		cout << "WARNING: removing the .db from the database name inputed" << endl;
		database.erase(database.length() - 3, 3);
	}
	database_loc = "smem_soar_databases/" + database + db_loc;
	database_cp_loc = "smem_soar_databases/" + database + db_cp_loc;

	if(!is_file_exist(database_loc.c_str())){
		cout << "ERROR: couldn't find database at " + database_loc << endl;;
		exit(1);
	}


    //get database name without path
    size_t found = database.find_last_of("/\\");
    string database_name = database.substr(found+1);


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
		
		word_tri.push_back(to_string(rat_size));
		word_tri.push_back(word1);
		word_tri.push_back(word2);
		word_tri.push_back(word3);
		word_tri.push_back(solution);

		rat_word_data.push_back(word_tri);
	}

	if(rand){
		 unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  		shuffle (rat_word_data.begin(), rat_word_data.end(), std::default_random_engine(seed));
	}

	cout << rat_size << endl;
	cout << rat_prob_file <<endl;

    //-------------------------------------------
	// Create an instance of the Soar kernel in our process
    Kernel* pKernel = sml::Kernel::CreateKernelInNewThread();
    
    cout << "Created Kernel" << endl;
   
    if (pKernel->HadError())
    {
        cout << pKernel->GetLastErrorDescription() << endl;
        return -1;
    }

    for (int j= num_attempt_start; j < num_attempt_end + 1; j++){
	    Agent* pAgent = pKernel->CreateAgent(("rat_test" + to_string(j)).c_str());
	    
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
	    pAgent->ExecuteCommandLine(soar_settings);
	    pAgent->ExecuteCommandLine(("srand 5 " + database_cp_loc).c_str());

	    //put three words on the input link
	    Identifier* pInputLink = pAgent->GetInputLink();
	        
	    Identifier* max_assoc;
	    if (mode == 'f') max_assoc = pAgent->CreateIdWME(pInputLink, "max-attempts");
	    if (mode == 'c') max_assoc = pAgent->CreateIdWME(pInputLink, "max_assoc");;
	    IntElement* max_num = pAgent->CreateIntWME(max_assoc, "num", j);

	    Identifier* pID_board = pAgent->CreateIdWME(pInputLink, "board");
	    Identifier* pID_card1 = pAgent->CreateIdWME(pID_board, "card");
	    Identifier* pID_card2 = pAgent->CreateIdWME(pID_board, "card");
	    Identifier* pID_card3 = pAgent->CreateIdWME(pID_board, "card");

	    StringElement* pID_word1 = pAgent->CreateStringWME(pID_card1, "word", " ");
	    StringElement* pID_word2 = pAgent->CreateStringWME(pID_card2, "word", " ");
	    StringElement* pID_word3 = pAgent->CreateStringWME(pID_card3, "word", " ");


		ofstream datFile;
		
		if (mode == 'f') {
			datFile.open(output_path + "/rat_out_freeRecall_" + to_string(j) + "_" + database_name + ".csv");
			datFile << "id,word1,word2,word3,solution,result,attempts,connections,correct" << endl;
		}
		if (mode == 'c') {
			datFile.open(output_path + "/rat_out_cued_" + database_name + ".csv");
			datFile << "id,word1,word2,word3,solution,result,connections,correct" << endl;

		}

		//loop through RAT problems  
		for (int i = 0; i < rat_word_data.size(); i++) {

			assert(rat_word_data[i].size() == 5);

			string id = rat_word_data[i][0];
			word1 = rat_word_data[i][1];
			word2 = rat_word_data[i][2];
			word3 = rat_word_data[i][3];
			solution = rat_word_data[i][4];

            datFile << id << "," << word1 << "," << word2 << "," << word3 << "," << solution << ",";

			cout << id << " " << word1 << " " << word2 << " " << word3 << endl;

			pAgent->Update(pID_word1, word1.c_str());
			pAgent->Update(pID_word2, word2.c_str());
			pAgent->Update(pID_word3, word3.c_str());
           
            if (mode == 'f') pAgent->Update(max_num, j);
			
			pAgent->Commit();

			int step = 0;			
			
			//run while there isn't any new output.
			do {
                step++;
                pAgent->RunSelf(1);
                if(step == 1){
                	//cout << pKernel->ExecuteCommandLine("print <s>",pAgent->GetAgentName()) << endl;
				}
                
            } while (!pAgent->Commands() && step < 400);

			if (step == 400) {
				cout << pKernel->ExecuteCommandLine("print s1 -d 5",pAgent->GetAgentName()) << endl;
				cout << "NA" << endl;
		
				switch (mode) {
				case 'c':
					datFile << "NA,0" << endl;
					break;
				case 'f':
					datFile << "NA,0,0" << endl;
					cout << "NA" << endl;
					break;
				}
			}
			else {
				//cout << pKernel->ExecuteCommandLine("print <s> -d 3",pAgent->GetAgentName()) << endl;


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
                    }
                    else{
                        datFile << '0' << endl;
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
		}//through 144
	}//through attempts
   
    pKernel->Shutdown() ;   // Deletes all agents (unless using a remote connection)
    delete pKernel ;        // Deletes the kernel itself
    
}
