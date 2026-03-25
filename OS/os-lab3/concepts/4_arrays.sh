#!/bin/bash
array=( 1 2 "Sultan" )
echo $array     #only prints 1st one
echo ${array[2]}
echo ${array[@]}  #prints all
array+=("Ahmed" 18)
echo ${array[*]}    #also prints all

echo "Length of Array:  ${#array[*]}"

#array slicing - syntax: ${array[source]:start:length}
echo ${array[*]:1}  #start at index 1 but no length specified so full array
echo ${array[*]:1:3}    #prints 3 elements from index 1

#associative arrays (key-value pairs)
declare -A keyArray     #declared like this, mandotory
keyArray=( [name]="Paul" [age]=20 )
keyArray[city]="NYC"    #adding
echo ${keyArray[name]}
echo ${keyArray[*]} #access all values, also use @
echo ${!keyArray[@]}    #access all keys

#string also array
stringing="Hello"
lengthStr=${#stringing}
upperStr=${stringing^^}
lowerStr=${stringing,,}
echo "String = $stringing and Length is $lengthStr and Uppercase is $upperStr and Lowercase is $lowerStr"