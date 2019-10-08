# Modeling the Remote Associates Test
Jule Schatz, Steven J. Jones, and John E. Laird (2018). An Architecture Approach 
to Modeling the Remote Associates Test, Proceedings of the 16th International 
Conference on Cognitive Modelling (ICCM). Madison, WI.

Link to paper: soar.eecs.umich.edu/pubs/schatz_iccm18.pdf

### To Run RAT script
1. Install and setup Soar and SML, details found at soar.eecs.umich.edu
2. Compile rat_script.cpp
  on my mac: g++ -L < path>/Soar-9.6/bin -I < path>/Soar-9.6/include rat_script.cpp -lSoar  -std=c++11 -o exeRAT
3. For mac run: export DYLD_LIBRARY_PATH=< path>/Soar/out/
4. Run executable (see below) <br/>


**FreeRecall**: $ ./exeRAT f \<T or F for random order of questions\> start_attempts end_attempts database output smemParameters  ratProblemsTextFile <br/>
ex) $ ./exeRAT f F 1 20 finalNormalizedVersions/_9_20_2019_hbc_single_trash_normalized output/FR_hbc_single_10_08_2019 "smem --set spreading-use-only both" raw_144.txt <br/> 

**Cued**: $ ./exeRAT c \<T or F for random order of questions\> database output smemParameters ratProblemsTextFile <br/> 
ex)./exeRAT c F final_versions/COCA-TG_8_30_2019 output/cocaCued_10_08_2019 "smem --set spreading-use-only both" raw_144.txt <br/>



## Files/Directories


**rat_script.cpp** This C++ SML script takes in a Soar database backup (.db file) and runs either the Cued or FreeRecall model on inputted RAT questions. (see above for how to run). It prints out the RAT question the agent is working on, what it guessed as the answer, and how many of the cue words are connected to the solution word. 

**raw_144.txt** A text file of the 144 RAT questions published by Bowden and Jung-Beeman 2003.

**models** A directory of the Soar code for the Free Recall and the Cued model.

**smem_script** A diretory with the code to create the .soar database files from word association data sets.

**RAT_sub_RELEASE.txt** The four RAT questions the sample data file in smem_script can answer
 
Bowden, E. M., & Jung-Beeman, M. (2003). Normative datafor 144 compound remote associate problems. BehaviorResearch Methods, Instruments, & Computers,35(4), 634–639
