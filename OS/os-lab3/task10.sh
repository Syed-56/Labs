#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: ./cleanup.sh <directory> <days>"
    echo "Example: ./cleanup.sh /home/sultan/docs 30"
    exit 1
fi

DIR=$1
DAYS=$2

if [ ! -d "$DIR" ]; then
    echo "Error: '$DIR' is not a valid directory"
    exit 1
fi
if ! [[ "$DAYS" =~ ^[0-9]+$ ]]; then    #regex to check if entered days are digit
    echo "Error: '$DAYS' is not a valid number"
    exit 1
fi

files_removed=0
dirs_removed=0
echo "Starting Cleanup"

while IFS= read -r file; do
    rm "$file"
    if [ $? -eq 0 ]; then    #check if rm succeed
        echo "Deleted File: $file"
        ((files_removed++))
    else 
        echo "Error deleting"
    fi
done < <(find "$DIR" -type f -mtime +$DAYS) #finds files (type f) of DAYS(eg 30) older

echo "Files Complete - Removing Directories"
while IFS= read -r dir; do
    rmdir "$dir"
        if [ $? -eq 0 ]; then
            echo "removed empty directory"
            ((dirs_removed++))
        else
            echo "Error removing directory"
        fi
done < <(find "$DIR" -mindepth 1 -type d -empty) #find directoryes (type d) which are empty and only has 1 level

echo "Cleanup Complete"
echo "File Removed = $files_removed and Directories = $dirs_removed"