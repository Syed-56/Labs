#!/bin/bash

function display_menu() {
	echo "1) Add new Task"
	echo "2) View All Tasks"
	echo "3) Display Tasks, sorted by priority"
	echo "4) Mark Task Completed"
	echo "5) Exit"
}

function validate_opt() {
	if [ $# -ne 1 ]; then
		echo "Invalid Option"
		return 1
	fi

	local opt=$1
	if [[ $opt -lt 1 || $opt -gt 5 ]]; then
		echo "Invalid Option"
                return 1
	fi
	return 0
}

function validate_priority() {
	p=$1
	if [[ p=="High" || p=="Low" || p=="Medium" ]]; then
		return 0
	else
		return 1
	fi
}

opt=0
declare -A tasks
while [ $opt -ne 5 ]
do
	display_menu
	read -p "Enter Option: " opt
	validate_opt $opt
	status=$?
	if [ $status -eq 1 ]; then
		continue
	fi

	if [ $opt -eq 1 ]; then
		read -p "Enter Task: " taskName
		read -p "Enter Prioriy: " priority
		if ! validate_priority "$priority"; then
			echo "Invalid Priority"
			read -p "Enter Prioriy: " priority
		fi
		tasks["$taskName"]="$priority"
		echo "Task $taskName added successfully"

	elif [ $opt -eq 2 ]; then
                echo -e  "Tasks:-\n ${!tasks[@]}"
		echo -e "Priorities:-\n ${tasks[*]}"
	elif [ $opt -eq 3 ]; then
                echo  "--- Tasks Sorted by Priority (1-5) ---"
    # Check if the list is empty first
   		 if [ ${#tasks[@]} -eq 0 ]; then
        		echo "No tasks to sort."
    		else
        # 1. Start a loop to feed data into the pipe
	       		 for t in "${!tasks[@]}"; do
            			echo "${tasks[$t]} $t"
        		done | sort -n | while read -r p name; do
            # 2. Re-format the output so it looks nice
            		echo "Priority: $p | Task: $name"
        	done
    		fi	
	elif [ $opt -eq 4 ]; then
                read -p "Enter Task: " taskName
		if [[ -v tasks["$taskName"] ]]; then
			unset tasks["$taskName"]
			echo "Task $taskName removed"
		else
			echo "Invalid Task"
		fi
	else
		break
	fi
done

