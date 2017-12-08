#!/bin/bash

date="name,sex,rollno,location"
oldIFS=$IFS
IFS=, #now,
for item in $date
do 
    echo Item: $item
done

IFS=$oldIFS
