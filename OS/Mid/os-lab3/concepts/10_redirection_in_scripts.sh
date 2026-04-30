#!/bin/bash
## if you dont want to print output to terminal or write it in a file. You can redirect it to /dev/null
#eg: cd /root &> /dev/null
# since > handles output and 2> handles error. &> handles both

#eg: entering a directory where we dont have permission
set -e
if cd /root &> /dev/null
then
    echo "I'm in root"
else 
    echo "Access Denied but msg is hidden"
fi

set -ex     #e flag stops script if any command fails and x flag prints every command before executing it
scriptName=$(basename "${0}")   #captures exact script name
echo "Running Script: $scriptName"
logger "Log: $scriptName started by the user $USER"     #sending msg to system log

ls .    #a working command
mkdir ./newFolder   #now suppose if this folder was existing, then due to enabling of -e flag, the script would've died here
echo "Finished Successfully"