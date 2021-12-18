#!/bin/bash

OUT='./pipex'

#MEM_CHECK
LOGFILE="logfile"
VALGRIND_CHECKER="-s --leak-check=full --show-leak-kinds=all --track-fds=yes -q"

#GREP SETTINGS
GREP_RED='ms=01;31'
GREP_GREEN='ms=01;32'

#PRINTF SETTINGS
RESET="\033[0m"
BLACK="\033[30m"
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"
BOLDBLACK="\033[1m\033[30m"
BOLDRED="\033[1m\033[31m"
BOLDGREEN="\033[1m\033[32m"
BOLDYELLOW="\033[1m\033[33m"
BOLDBLUE="\033[1m\033[34m"
BOLDMAGENTA="\033[1m\033[35m"
BOLDCYAN="\033[1m\033[36m"
BOLDWHITE="\033[1m\033[37m"


function error_testing () {
	cat /dev/null > $4
	ERROR_MESSAGE_EXPECTED_FILE="error_expected"
	ERROR_MESSAGE_OBTAINED_FILE="error_obtained"
	2>$ERROR_MESSAGE_EXPECTED_FILE < $1 $2 | 2>>$ERROR_MESSAGE_EXPECTED_FILE $3 > $4
	ERROR_CODE_EXPECTED=$?
	echo "$OUT $1 '$2' '$3' $4"
	2>$ERROR_MESSAGE_OBTAINED_FILE valgrind $VALGRIND_CHECKER --log-file=$LOGFILE $OUT $1 "$2" "$3" $4
	ERROR_CODE_OBTAINED=$?
	sed -i "s/.*:.*: \(.*:.*\)$/\1/" $ERROR_MESSAGE_EXPECTED_FILE
	diff $ERROR_MESSAGE_EXPECTED_FILE $ERROR_MESSAGE_OBTAINED_FILE > /dev/null
	DIFF_RETURNED_CODE=$?
	if [ $DIFF_RETURNED_CODE = 0 ]
	then
		printf $GREEN"Error message expected and obtained are identical.\n"$RESET
	else
		printf $RED"Error message expected and obtained are not identical.\n"$RESET
		echo "expected :"
		cat -e $ERROR_MESSAGE_EXPECTED_FILE
		echo "obtained :"
		cat -e $ERROR_MESSAGE_OBTAINED_FILE
	fi
	if [ $ERROR_CODE_EXPECTED = $ERROR_CODE_OBTAINED ]
	then
		printf $GREEN"Both returned code are identical !!!\n"$RESET
	else
		printf $RED"Returned code not identical, expected is $ERROR_CODE_EXPECTED and obtained is $ERROR_CODE_OBTAINED.\n"$RESET
	fi	
	export GREP_COLORS=$GREP_RED
	grep -A 5 --color=always "LEAK SUMMARY" $LOGFILE
	rm -f $LOGFILE $ERROR_MESSAGE_EXPECTED_FILE $ERROR_MESSAGE_OBTAINED_FILE $4
}

#test_inFile cmd1 cmd2 test_outFile
function functionnal_testing()
{
	cat /dev/null > $4
	TMP_INFILE="tmp_infile"
	TMP_OUTFILE="tmp_outfile"
	cp $1 $TMP_INFILE
	< $TMP_INFILE $2 | $3 > $TMP_OUTFILE
	OUTPUT_EXPECTED_CODE=$?
	valgrind $VALGRIND_CHECKER --log-file=$LOGFILE $OUT $1 "$2" "$3" $4
	OUTPUT_OBTAINED_CODE=$?
	echo "$OUT $1 '$2' '$3' $4"
	diff -s $4 $TMP_OUTFILE > /dev/null
	DIFF_RETURNED_CODE=$?
	if [ $DIFF_RETURNED_CODE = 0 ]
	then
		printf $GREEN"Both output files are identical.\n"$RESET
	else
		printf $RED"Output files are not identical.\n"$RESET
	fi
	if [ $OUTPUT_OBTAINED_CODE = $OUTPUT_EXPECTED_CODE ]
	then
		printf $GREEN"Both returned code are identical !!!\n"$RESET
	else
		printf $RED"Returned code not identical, expected is $OUTPUT_EXPECTED_CODE and obtained is $OUTPUT_OBTAINED_CODE.\n"$RESET
	fi	
	export GREP_COLORS=$GREP_RED
	grep -A 5 --color=always "LEAK SUMMARY" $LOGFILE
	rm -f $TMP_INFILE $TMP_OUTFILE $LOGFILE $4
}

make -s
echo "----------Should return error----------"
#CASE 1 2 3 4
	error_testing "1" "2" "3" "4"
#CASE inFile 2 3 4
	error_testing "inFile" "2" "3" "4"
#CASE 1 2 3 outFile
	error_testing "1" "2" "3" "outFile"
#CASE inFile 2 3 outFile
	error_testing "inFile" "2" "3" "outFile"
#CASE inFile cat 3 outFile
	error_testing "inFile" "cat" "3" "outFile"
#CASE inFile 2 wc outFile
	error_testing "inFile" "2" "wc" "outFile"
#CASE 1 cat wc 4
	error_testing "1" "cat" "wc" "4"
echo "----------Functionnal testing----------"
#CASE inFile cat wc outFile
	functionnal_testing "inFile" "cat" "wc" "outFile"
#CASE inFile "cat -e" "wc -l" outFile
	functionnal_testing "inFile" "cat -e" "wc -l" "outFile"
#CASE inFile "grep a1" "wc -w" outFile
	functionnal_testing "inFile" "grep a1" "wc -w" "outFile"
#CASE inFile "grep a1" "hostname" outFile
	functionnal_testing "inFile" "grep a1" "hostname" "outFile"
