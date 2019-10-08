# Modeling the Remote Associates Test
Jule Schatz, Steven J. Jones, and John E. Laird (2018). An Architecture Approach 
to Modeling the Remote Associates Test, Proceedings of the 16th International 
Conference on Cognitive Modelling (ICCM). Madison, WI.

Link to paper: soar.eecs.umich.edu/pubs/schatz_iccm18.pdf


### To Run
1. Install and setup Soar and SML, details found at soar.eecs.umich.edu
2. Compile rat_script.cpp
  on my mac: g++ -L < path>/Soar-9.6/bin -I < path>/Soar-9.6/include rat_script.cpp -lSoar  -std=c++11
3. For mac run: export DYLD_LIBRARY_PATH=< path>/Soar/out/
4. Run executable:  ./exe < f(ree recall model) or c(ued retrieval model)> < attempts> < database name> < rat problems text file>
   
   for example:  ./a.out   f   15   sub_hbc_single_trash   raw_144_sub.txt
