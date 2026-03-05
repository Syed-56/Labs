#!/bin/bash
#first line specifies bash path and echo means print
echo "Hello World"

#when initializing/updating dont give space around =.
name="Sultan"
age=18
#-n means that the next echo will be printed without new line
echo -n  "My name is $name and age is $age"
echo " So cool"
age=19
#no "" when only printing variable, variable is indicated by $
echo $age

#array - datatype dont matter in bash and no , in arrays
arr=(10 2.4 "Sultan")
echo $arr	#only prints 1st element
echo ${arr[2]}	#arrays are accesed like this
echo -e "\n"
arr+=("Ahmed")	#append element in array
echo ${arr[*]}	#print whole array

#loops
for i in 1 2 3 4 5
do
	echo -n "$i  "
done 
echo ""
i=0
for element in "${arr[@]}"
do	
	((i+=1))
	echo "$i $element"
done
#in increment: u can also do ((i++)) or i=$((i+1))
# every arithmetic operation use brackets like ((num1*num2))

#input and if else
read color	#to read with a prompt do read -p "msg
predefined="purple"
#if is used like that. for comparison do ==, -gt (for >) and -lt (for <)
if [ "$color" == "predefined" ]
then
#instead of writing if then seperate lines we can do if [ .. ]; then
	echo "Color and Predefined are both same"
else
	echo "different"	
fi
#string manipulate
echo ${#color}
echo ${color:0:3}

#we can also use case statement
#case $variable in
#    pattern1)
#        # commands to run if pattern1 matches
#        ;;
#    pattern2)
#        # commands to run if pattern2 matches
#        ;;
#    *)
#        # the "catch-all" (if nothing else matches)
#        ;;
#esac

