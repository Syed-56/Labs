#!/bin/bash
count=0
while IFS= read -r line; do
    for word in $line;  do
        if [ "$word" == "LINUX" ]; then
            echo "Found Linux - $line"
            ((count++))
        fi
    done
done < practice.sh
echo "count = $count"