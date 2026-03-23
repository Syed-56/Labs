#!/bin/bash
#basically arguments can also be passed when calling the file from terminal. Also accessed like function ones
echo "Script Name: $0"
echo "Total Arguments: $#"

if [ $# -lt 2 ]
then
    echo "Error! Invalid Arguments"
    exit 1
fi

echo "Hello $1 ! You are $2 years old"  

#shifting arguments - for long list of arguments, if you use a shift, the $1 gets discarded and $2 becomes $1 and so on
#eg: processing a list
total=0
echo "Starting with $# arguments"
while [ $# -gt 0 ]
do
    echo "Processing $1"
    ((total++))
    shift
done
echo "Total Processed: $total"

# we can also shift multiple positions like doing shift 2 means $3 becomes $1 and $4 becomes $2 and both $1,$2 are discarded