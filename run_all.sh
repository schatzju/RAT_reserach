#create folder with date
OUTPUT_NAME="output/rat_run_"`date +"%d_%m_%Y"`

mkdir $OUTPUT_NAME

./a.out c 0 smem_soar_databases/hbc_single_8_26_18 $OUTPUT_NAME
./a.out f 20 smem_soar_databases/hbc_single_8_26_18 $OUTPUT_NAME

./a.out f 20 smem_soar_databases/hbc_single_subset_8_26_18 $OUTPUT_NAME
./a.out c 0 smem_soar_databases/hbc_single_subset_8_26_18 $OUTPUT_NAME

./a.out f 20 smem_soar_databases/hbc_single_trash_8_26_18 $OUTPUT_NAME
./a.out c 0 smem_soar_databases/hbc_single_trash_8_26_18 $OUTPUT_NAME
