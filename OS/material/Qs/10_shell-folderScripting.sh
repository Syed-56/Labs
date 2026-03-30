#!/bin/bash

while true
do
	echo -e  "\nOS Menu\n1) Create Folder\n2)List Folders\n3)Count Folders\n"
        read -p "Enter Option: " opt
        if [[ opt -gt 3 || opt -lt 0 ]]; then
                echo -e "Invalid Option\n"
                continue
        fi
	
	if [ $opt -eq 1 ]; then
		#create folder
	fi

	if [ $opt -eq 2 ]; then
                #list folder
        fi

	if [ $opt -eq 3 ]; then
                #count folder
        fi


done
