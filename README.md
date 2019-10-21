# Modeling the Remote Associates Test
Jule Schatz, Steven J. Jones, and John E. Laird (2018). An Architecture Approach 
to Modeling the Remote Associates Test, Proceedings of the 16th International 
Conference on Cognitive Modelling (ICCM). Madison, WI.

Link to paper: soar.eecs.umich.edu/pubs/schatz_iccm18.pdf

### To Run the RAT script
1. Install and setup Soar and SML, details found at soar.eecs.umich.edu
2. Compile rat_script.cpp
  on my mac: g++ -L < path>/Soar-9.6/bin -I < path>/Soar-9.6/include rat_script.cpp -lSoar --std=c++11 -o exeRAT
3. For mac run: export DYLD_LIBRARY_PATH=< path>/Soar/out/
4. Run executable (see below) <br/>


**FreeRecall**: $ ./exeRAT f \<T or F for random order of questions\> start_attempts end_attempts database output smemParameters  ratProblemsTextFile <br/>
ex) $ ./exeRAT f F 1 20 subRELEASE_10_8_2019_hbc_single_trash output/FR_hbc_single_sub_10_08_2019 "smem --set spreading-use-only both" RAT_sub_RELEASE.txt <br/> 

**Cued**: $ ./exeRAT c \<T or F for random order of questions\> database output smemParameters ratProblemsTextFile <br/> 
ex)./exeRAT c F subRELEASE_10_8_2019_hbc_single_trash output/FR_hbc_single_sub_10_08_2019 "smem --set spreading-use-only both" RAT_sub_RELEASE.txt <br/> 


## Files/Directories

**output** A directory where the output from the rat_script is saved

**smem_soar_databases** A directory where .soar and .db files are stored and saved from smem scripts

**rat_script.cpp** This C++ SML script takes in a Soar database backup (.db file) and runs either the Cued or FreeRecall model on inputted RAT questions. (see above for how to run). It prints out the RAT question the agent is working on, what it guessed as the answer, and how many of the cue words are connected to the solution word. 

**raw_144.txt** A text file of the 144 RAT questions published by Bowden and Jung-Beeman 2003.

**models** A directory of the Soar code for the Free Recall and the Cued model.

**smem_script** A diretory with the code to create the .soar database files from word association data sets.

**RAT_sub_RELEASE.txt** The four RAT questions the sample data file in smem_script can answer
 
Bowden, E. M., & Jung-Beeman, M. (2003). Normative datafor 144 compound remote associate problems. BehaviorResearch Methods, Instruments, & Computers,35(4), 634–639

## How to run the Soar agents without the SML C++ script
Go to RAT_research/models/cued_soar_agent or RAT_research/models/freeRecall_soar_agent <br/> 

Open *load_cards_wm.soar* <br/> 
On line 5 and line 17 change “io.input-link.board <board>” to “iox.input-link.board <board>”<br/> 
*This changes the agent to work without the SML script and instead take the input from the initialization rule<br/> 

*initialize.soar* <br/> 
On line 44, 46, 48 you can specify which RAT item you would like the system to solve. This is instead of reading it in from the C++ script. Currently it will attempt the question “night” “wrist” and “stop”<br/> 

*_load.soar* <br/> 
Uncomment line 29 and 30 <br/> 
<br/> 
On line 29 specify the path to a .db backed up soar database file. Note that once you have run the agent with that database file once it will not work correctly again. Therefore, before every run of the agent I delete the database_cp.db file and make a copy of the database.db file named database_cp.db <br/> 

Now you should be able to open soar, load in the *_load.soar* file and run the agent locally on one problem. 


