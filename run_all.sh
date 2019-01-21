#create folder with date
OUTPUT_NAME_NO_FAN="output/rat_run_no_fan_"`date +"%d_%m_%Y"`
OUTPUT_NAME_NO_ASSOC="output/rat_run_no_assoc_"`date +"%d_%m_%Y"`
OUTPUT_NAME="output/rat_run_"`date +"%d_%m_%Y"`

#mkdir $OUTPUT_NAME_NO_FAN
#mkdir $OUTPUT_NAME_NO_ASSOC
mkdir $OUTPUT_NAME

#./a.out f 1 1 hbc_single_8_26_18 $OUTPUT_NAME
#./a.out f 1 4 hbc_single_8_26_18 $OUTPUT_NAME_NO_FAN "smem --set spreading-use-only association"
#./a.out f 1 4 hbc_single_8_26_18 $OUTPUT_NAME_NO_ASSOC "smem --set spreading-use-only fan"
./a.out f T 1 3 thresh2_1_7_2019_hbc_single $OUTPUT_NAME "smem --set spreading-use-only both" 


#./a.out f 1 20 hbc_single_subset_8_26_18 $OUTPUT_NAME
./a.out c T thresh2_1_7_2019_hbc_single $OUTPUT_NAME "smem --set spreading-use-only both" 

