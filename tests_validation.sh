#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
export GREP_COLORS='ms=01;32'

make -s
echo "Should return error"
printf "./pipex 1 2 3 4 5 >> "
./pipex 1 2 3 4 5 | grep --color=always "Error"
printf "./pipex 1 2 3 4 >> "
./pipex 1 2 3 4 | grep --color=always "Error"
printf "./pipex inFile 2 3 4 >> "
./pipex inFile 2 3 4 | grep --color=always "Error"
printf "./pipex 1 2 3 outFile >> "
./pipex 1 2 3 outFile| grep --color=always "Error"
echo "Should not return error"
./pipex inFile 2 3 outFile







export GREP_COLORS='ms=01;31'







