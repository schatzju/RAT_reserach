# Modeling the Remote Associates Test
Jule Schatz, Steven J. Jones, and John E. Laird (2018). An Architecture Approach 
to Modeling the Remote Associates Test, Proceedings of the 16th International 
Conference on Cognitive Modelling (ICCM). Madison, WI.

Link to paper: soar.eecs.umich.edu/pubs/schatz_iccm18.pdf


### To Run
1. Install and setup Soar and SML, details found at soar.eecs.umich.edu
2. Compile rat_script.cpp
  on my mac: g++ -L < path>/Soar-9.6/bin -I < path>/Soar-9.6/include rat_script.cpp -lSoar  -std=c++11 -o exeRAT
3. For mac run: export DYLD_LIBRARY_PATH=< path>/Soar/out/
4. Run executable 
##FreeRecall: $ ./exeRAT <t or f for random order of questions> F start_attempts end_attempts database output smemParameters ratProblemsTextFile
ex) $ ./exeRAT f F 1 20 finalNormalizedVersions/_9_20_2019_hbc_single_trash_normalized output/FR_hbc_single_10_08_2019 
      "smem --set spreading-use-only both" raw_144.txt

##Cued: $ ./exeRAT <t or f for random order of questions> C database output smemParameters ratProblemsTextFile
ex)./exeRAT c F final_versions/COCA-TG_8_30_2019 output/cocaCued_10_08_2019 "smem --set spreading-use-only both" raw_144.txt
