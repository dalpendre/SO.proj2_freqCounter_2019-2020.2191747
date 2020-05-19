#!/bin/bash

#
# Simple script to run ./freqCounter ($EXE) under some testing scenarios.
# SO 2S 2019-2020
#

#--------------------------------------------------------------------
# Config
#--------------------------------------------------------------------
# Executable
EXE="./freqCounter"
# Dir to hold result files
RESULTS_DIR="/tmp/RESULTS"

#--------------------------------------------------------------------
# Code
#--------------------------------------------------------------------
# --mode 1 and --mode 2
function run_with_one_file {
	input_file=$1
	exe=$2
	results_dir=$3

	if [ ! -f ${input_file} ]; then
		printf "Cannot find file '%s' - exiting\n" ${input_file} 
		exit 1
	fi 

	results_basename="${results_dir}/${input_file}_MODE"

	results="${results_basename}.txt"
	date "+%Y.%m.%d_%Hh%M.%S" > ${results}
	for modeNum in 1 2
	do
		echo "------------------------------------------------------------" | tee -a ${results}
		# Mode "modeNum"
		echo "$exe --mode $modeNum ${input_file}" | tee -a ${results}
		$exe --mode $modeNum --file ${input_file} >> ${results}
		# Compact
		echo "$exe --mode $modeNum --file ${input_file} --compact" | tee -a ${results}
		$exe --mode $modeNum --file "$input_file" --compact  >> ${results}
	done
}


# --search
function search_one_file {
	input_file=$1
	exe=$2
	results_dir=$3
	search_hex=$4

	if [ ! -f ${input_file} ]; then
		printf "Cannot find file '%s' - exiting\n" ${input_file} 
		exit 1
	fi 

	results_basename="${results_dir}/${input_file}_SEARCH"

	results="${results_basename}.txt"
	echo "==[SEARCH]====================================" >> ${results}
	date "+%Y.%m.%d_%Hh%M.%S" >> ${results}
	echo "$exe -s ${search_hex} --file $input_file" | tee -a ${results}
	echo "---------------------------------------" | tee -a ${results}
	$exe --search ${search_hex} --file "$input_file" >> ${results}
}



#====================================================================
# main code
#====================================================================

# Create $RESULTS_DIR directory
if [ ! -d "$RESULTS_DIR" ]; then
	mkdir "$RESULTS_DIR"
fi


if [ ! -f ${EXE} ]; then
	printf "Cannot find executable '%s' - exiting\n" ${EXE} 
	exit 1
fi 

# Fonte: 
# https://www.ipleiria.pt/normasgraficas/wp-content/uploads/sites/80/2016/07/Politecnico_png.zip
inputFile="Politecnico_png.zip"
run_with_one_file "$inputFile" "$EXE" "$RESULTS_DIR"
search_str="0x504B"  # PK
search_one_file "$inputFile" "$EXE" "$RESULTS_DIR" "$search_str"

# Enunciado do projeto 2 - versão 4
inputFile="EI_SO.2S2019-20.proj2_freqCounter_V04.pdf"
run_with_one_file "$inputFile" "$EXE" "$RESULTS_DIR"
search_str="0x504446"	# 0x504446="PDF"
search_one_file "$inputFile" "$EXE" "$RESULTS_DIR" "$search_str"

inputFile="EI_SO_D+PL_2019-20_chap_09---filesystems_PT_v2.pdf"
run_with_one_file "$inputFile" "$EXE" "$RESULTS_DIR"
search_str="0x504446"
search_one_file "$inputFile" "$EXE" "$RESULTS_DIR" "$search_str"
search_str="0x436f756e74"
search_one_file "$inputFile" "$EXE" "$RESULTS_DIR" "$search_str"


# Info
echo "Result files are in '$RESULTS_DIR' directory"

