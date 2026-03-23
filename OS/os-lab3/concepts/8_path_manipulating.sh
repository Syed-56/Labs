#!/bin/bash
FILE="~/Documents/Labs/OS/mid-syllabus.txt"
fileName=$(basename "$FILE")
dirName=$(dirname "$FILE")
fullPath=$(realpath "$FILE")

echo "Full String: $File"
echo "File Name: $fileName"
echo "Directory Name: $dirName"
echo "Full Path: $fullPath"

#consider this code
# FILE=$1
# fileName=$(basename "$FILE")
# cp "$FILE" "/tmp/$fileName.backup"
#you created a script where user run script and give path to a file to create backup so you can use this manipulation for it
#example: ./backup_script.sh data.txt

#check if file or folder exist
folder="../os-lab3"
if [ -d $folder ]
then
    echo "$folder exists"
else 
    echo "$folder dont exists"
fi

filePath="../../mid-syllabus.txt"
if [! -f filePath ]
then 
    echo "$filePath exists"
else 
    echo "$filePath exists"
fi

#-d -f are is directory and is file flags we used. theres other flags too
#-s for if the the file has a size (not empty). #-e for if the exists (means true path given). -r for if the file is readable (you have permission)