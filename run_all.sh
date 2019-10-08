# #create folder with date
# OUTPUT_NAME_NO_FAN="output/FR_hbc_single_trash_no_fan_normalized_"`date +"%d_%m_%Y"`
# OUTPUT_NAME_NO_ASSOC="output/FR_hbc_single_trash_no_assoc_normalized_"`date +"%d_%m_%Y"`
# OUTPUT_NAME_NEITHER="output/FR_hbc_single_trash_neither_normalized_"`date +"%d_%m_%Y"`

# OUTPUT_NAME_DOUBLE="output/FR_double__normalized_"`date +"%d_%m_%Y"`
# OUTPUT_NAME_CLEANED="output/FR_cleaned_normalized_"`date +"%d_%m_%Y"`
# OUTPUT_NORMAL="output/FR_hbc_single_trash_normalized_"`date +"%d_%m_%Y"`

#OUTPUT_NAME_CUED_HBC="output/C_hbc_single_trash_normalized_"`date +"%d_%m_%Y"`
#OUTPUT_NAME_CUED_COCA="output/c_COCA_"`date +"%d_%m_%Y"`
# # OUTPUT_NAME_FR_COCA="output/final_rat_run_FR_COCA_"`date +"%d_%m_%Y"`

#OUTPUT_NAME_CUED_DOUBLE_HBC="output/C_hbc_double_trash_normalized_"`date +"%d_%m_%Y"`

OUTPUT_NAME_REVERSE_FR="output/FR_hbc_single_trash_reverse_normalized_"`date +"%d_%m_%Y"`
#OUTPUT_NAME_REVERSE_C="output/C_hbc_single_trash_reverse_normalized_"`date +"%d_%m_%Y"`

# OUTPUT_NAME_FREQ_LOW="output/FR_hbc_single_trash_freq_t.1000_m.1_normalized_"`date +"%d_%m_%Y"`

# OUTPUT_NAME_FREQ_HIGH="output/FR_hbc_single_trash_freq_t.1_m.100_normalized_"`date +"%d_%m_%Y"`



# mkdir $OUTPUT_NAME_NO_FAN
# mkdir $OUTPUT_NAME_NO_ASSOC
# mkdir $OUTPUT_NAME_NEITHER

# mkdir $OUTPUT_NAME_DOUBLE
# mkdir $OUTPUT_NAME_CLEANED
# mkdir $OUTPUT_NORMAL

# mkdir $OUTPUT_NAME_CUED_HBC
# mkdir $OUTPUT_NAME_CUED_COCA

# mkdir $OUTPUT_NAME_CUED_DOUBLE_HBC
mkdir $OUTPUT_NAME_REVERSE_FR
#mkdir $OUTPUT_NAME_REVERSE_C

# mkdir $OUTPUT_NAME_FREQ_LOW
# mkdir $OUTPUT_NAME_FREQ_HIGH

# #no assoc
# ./exeRAT f F 1 20 finalNormalizedVersions/_9_20_2019_hbc_single_trash_normalized $OUTPUT_NAME_NO_ASSOC "smem --set spreading-use-only fan" raw_144.txt

# #no fan
# ./exeRAT f F 1 20 finalNormalizedVersions/_9_20_2019_hbc_single_trash_normalized $OUTPUT_NAME_NO_FAN "smem --set spreading-use-only association" raw_144.txt

# #neither
# ./exeRAT f F 1 20 finalNormalizedVersions/_9_20_2019_hbc_single_trash_normalized $OUTPUT_NAME_NEITHER "smem --set spreading-use-only neither" raw_144.txt

# #double trash
# ./exeRAT f F 1 20 finalNormalizedVersions/_9_24_2019_hbc_double_trash_normalized $OUTPUT_NAME_DOUBLE "smem --set spreading-use-only both" raw_144.txt

# #single cleaned
# ./exeRAT f F 1 20 finalNormalizedVersions/unixDict_9_24_2019_hbc_single_cleaned_normalized $OUTPUT_NAME_CLEANED "smem --set spreading-use-only both" raw_144.txt

# #normal
# ./exeRAT f F 1 20 finalNormalizedVersions/_9_20_2019_hbc_single_trash_normalized $OUTPUT_NORMAL "smem --set spreading-use-only both" raw_144.txt

#cued HBC
#./exeRAT c F finalNormalizedVersions/_9_20_2019_hbc_single_trash_normalized $OUTPUT_NAME_CUED_HBC "smem --set spreading-use-only both" raw_144.txt

#cued COCA
#./exeRAT c F final_versions/COCA-TG_8_30_2019 $OUTPUT_NAME_CUED_COCA "smem --set spreading-use-only both" raw_144.txt


# #cued HBC double
#./exeRAT c F finalNormalizedVersions/_9_24_2019_hbc_double_trash_normalized $OUTPUT_NAME_CUED_DOUBLE_HBC "smem --set spreading-use-only both" raw_144.txt

# #reversed FR
./exeRAT f F 1 20 finalNormalizedVersions/reversed_9_28_2019_hbc_single_trash_normalized $OUTPUT_NAME_REVERSE_FR "smem --set spreading-use-only both" raw_144.txt

# #reversed C
#./exeRAT c F finalNormalizedVersions/reversed_9_28_2019_hbc_single_trash_normalized $OUTPUT_NAME_REVERSE_C "smem --set spreading-use-only both" raw_144.txt

# #freq low
# ./exeRAT f F 1 20 finalNormalizedVersions/freqTime1000_freqScale1.000000freq_9_24_2019_hbc_single_trash_normalized $OUTPUT_NAME_FREQ_LOW "smem --set spreading-use-only both" raw_144.txt

# #freq high
# ./exeRAT f F 1 20 finalNormalizedVersions/freqTime1_freqScale100.000000freq_9_24_2019_hbc_single_trash_normalized $OUTPUT_NAME_FREQ_HIGH "smem --set spreading-use-only both" raw_144.txt

# ##cued COCA
# ./exeRAT c F final_versions/COCA-TG_8_30_2019 $OUTPUT_NAME_CUED_COCA "smem --set spreading-use-only both" raw_144.txt

# ##FR COCA
# ./exeRAT f F 1 20 final_versions/COCA-TG_8_30_2019 $OUTPUT_NAME_FR_COCA "smem --set spreading-use-only both" raw_144.txt
# #


# #
# ##./a.out c T thresh2_1_7_2019_hbc_single $OUTPUT_NAME "smem --set spreading-use-only both"
# #
