#!/bin/bash

#read content from a file
while read -r var   #use -r to avoid escaping backslash
do
    echo $var
done < basics.sh

#read content from a csv file
while IFS="," read -r f1 f2 f3
do
    echo $f1
    echo $f2
    echo $f3
done <data.csv

#another way
cat data.csv | awk awk 'NR>1' | 
while IFS="," read -r f1 f2 f3
do
    echo "$f1, $f2, $f3"
done