#!/bin/bash
echo "1: Displat Date\n2: List Files\n3: Show current directory\n4: Exit"
read -p "Enter Choice: " choice
case $choice in
	1) date;;
	2) ls;;
	3) pwd;;
esac
if [[ $choice != 1 && $choice != 2 && $choice != 3 && $choice != 4 ]]
then
	echo "Invalid"
fi

