#!/bin/bash

if [ $# -ne 2 ]; then   # $# is number of args
    echo "Error - do ./task9.sh <directory> <pattern>"
    exit 1
fi

#we studied in function one that args are like $1, $2, ...
#so here directory is $1 and pattern is $2
DIR=$1
PATTERN=$2

if [ ! -d $DIR ]; then    #!=not, -d = directory check flag
    echo "Error - Invalid directory"
    exit 1
fi

files=("$DIR"/*) #move all items in directory into variable
if [ ! -e "${files[0]}" ]; then   #check if first item in files variable exist (dir not empty)
    echo "Error - empty directory"
    exit 1
fi

#counter to track files
count=0
success=0
failed=0

for file in "${files[@]}"; do
    if [ -f "$file" ]  ; then   #-f check if its a file not a folder
        ext="${file##*.}"    #get extension
        newName="$DIR/${PATTERN}${count}.${ext}"
        if mv "$file" "$newName"; then
            echo "Renamed $file to $newName"
            ((count++))
            ((success++))
        
        else 
            echo "Errer renaming $file"
            ((failed++))
        fi
    fi
done

echo "Renamed $success files successfully"
if [ $failed -gt 0 ]; then
    echo "Warning - failed to rename $failed files"
fi
