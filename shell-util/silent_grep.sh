#!/bin/bash -xv
#file name silect_grep.sh
#use to test whether file contain desired content


if [ $# -ne 2 ]; then 
    echo "Usage: $0 match_test filename"
    exit 1
fi

match_test=$1
filename=$2

grep -q "$match_test" $filename

if [ $? -eq 0 ]; then
    echo "The test exists in the file"
else
    echo "Text does not exist in the file"
fi
