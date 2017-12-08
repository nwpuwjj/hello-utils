#!/bin/bash

data="name,sex,rollno,location"
oldIFS=$IFS
echo wjj$oldIFS  wjj
IFS=, #now
for item in $data;
do
    echo Item: $item
done

IFS=$oldIFS
