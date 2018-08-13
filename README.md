# Modeling the Remote Associates Test
Jule Schatz, Steven J. Jones, and John E. Laird (2018). An Architecture Approach 
to Modeling the Remote Associates Test, Proceedings of the 16th International 
Conference on Cognitive Modelling (ICCM). Madison, WI.

Link to paper: soar.eecs.umich.edu/pubs/schatz_iccm18.pdf


### To Run
1. install and setup Soar and SML, details found at soar.eecs.umich.edu
2. compile rat_script.cpp
  on my mac: g++ -L /Users/schatzju/Documents/Soar-9.6/bin -I /Users/schatzju/Documents/Soar-9.6/include rat_script.cpp -lSoar  std=c++11
3. For mac run: export DYLD_LIBRARY_PATH=/Users/schatzju/Documents/Soar/out/
4. run executable:  ./a.out <f or c> <attempts> <database name> <rat problems text file>
   for example:  ./a.out f 15 sub_hbc_single_trash raw_144_sub_test.txt
