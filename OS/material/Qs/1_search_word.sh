#!/bin/bash

function search_word() {
	if [ $# -lt 2 ]
	then
		echo "Error: Invalid Arguments"
		return 1
	fi

	local word=$1
	local filename=$2

	if grep -n $word $filename 
	then
		echo "Search Successfull"
	else
		echo "Search Failed"
	fi
}

search_word "output" 1_basics.sh 
