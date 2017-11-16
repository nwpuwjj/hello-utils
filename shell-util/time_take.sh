#!/bin/bash
#file name time_take.sh
start=$(date +%s)
#commands;
#statements;
sleep 2;
end=$(date +%s)
difference=$((end - start))
echo Time taken to execute commands is $difference seconds
