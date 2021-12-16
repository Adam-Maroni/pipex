#!/bin/bash

OUT='./pipex'

#MEM_CHECK
LOGFILE="logfile"
VALGRIND_CHECKER="-s --leak-check=full --show-leak-kinds=all --track-fds=yes -q"

#GREP SETTINGS
RED='ms=01;31'
GREEN='ms=01;32'

function error_testing () {
	echo -n "$OUT $1 >> "
	export GREP_COLORS=$GREEN
	valgrind $VALGRIND_CHECKER --log-file=$LOGFILE $OUT $1 | grep --color=always -i "Error"
	export GREP_COLORS=$RED
	grep -A 5 --color=always "LEAK SUMMARY" $LOGFILE
	rm -f $LOGFILE
}

#test_inFile cmd1 cmd2 test_outFile
function functionnal_testing()
{
	cat /dev/null > $4
	TMP_INFILE="tmp_infile"
	TMP_OUTFILE="tmp_outfile"
	touch $TMP_OUTFILE
	cp $1 $TMP_INFILE
	< $TMP_INFILE $2 | $3 > $TMP_OUTFILE
	valgrind $VALGRIND_CHECKER --log-file=$LOGFILE $OUT $1 "$2" "$3" $4
	export GREP_COLORS=$GREEN
	echo -n "$OUT $1 '$2' '$3' $4 >> "
	diff -s $4 $TMP_OUTFILE | grep --color=always "identical"
	export GREP_COLORS=$RED
	grep -A 5 --color=always "LEAK SUMMARY" $LOGFILE
	rm -f $TMP_INFILE $TMP_OUTFILE $LOGFILE
}

make -s
echo "----------Should return error----------"
#CASE 1 2 3 4 5
	error_testing "1 2 3 4 5"
#CASE 1 2 3 4
	error_testing "1 2 3 4"
#CASE inFile 2 3 4
	error_testing "inFile 2 3 4"
#CASE 1 2 3 outFile
	error_testing "1 2 3 outFile"
#CASE inFile 2 3 outFile
	error_testing "inFile 2 3 outFile"
#CASE inFile cat 3 outFile
	error_testing "inFile cat 3 outFile"
#CASE inFile 2 wc outFile
	error_testing "inFile 2 wc outFile"
#CASE 1 cat wc 4
	error_testing "1 cat wc 4"
echo "----------Functionnal testing----------"
#CASE inFile cat wc outFile
	functionnal_testing "inFile" "cat" "wc" "outFile"
#CASE inFile "cat -e" "wc -l" outFile
	functionnal_testing "inFile" "cat -e" "wc -l" "outFile"
#CASE inFile "grep a1" "wc -w" outFile
	functionnal_testing "inFile" "grep a1" "wc -w" "outFile"
