# smem_Soar
Code to create semantic memory .soar files from raw word association data.   

### To Run
./exe \<false if not cleaned\> \<dictionary file if cleaned\> wordAssociationFile frequencyTime frequencyScale \<optional file name addition\></br>
  or</br>
./exe Coca </br>

#### Examples
./exe false single HBC_associations_2017.03.31_orig.csv 0 0 </br>
./exe dictionaries/unix_dictionary.txt single HBC_associations_2017.03.31_orig.csv 0 0 unixDict </br>
./exe false single HBC_associations_2017.03.31_orig.csv 1 100 freq </br> </br>
*For a reversed knowledge base go into the code and change in write_data.cpp line 35-62 following the directions there*</br>
(^^not ideal but already had wayyy to many parameters)
