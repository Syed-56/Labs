#!/bin/bash
#This is a comment

#sending output to terminal
echo "Hello World"

#variables - syntax: varName=value (no space around =) and are accessed using $
var=150
echo "Value of var = $var"
#we also have constant variables in it
readonly Pi=3.142

#to print newline
echo -e "\n"

#input output
echo "Enter Your Name"
read name
echo "Your name is $name"
#to prompt and input in single line
read -p "Tell your name again: " $name

#random and uid
echo $RANDOM
echo $UID
#common task: find a number between 1 and 100
number=$(( ($RANDOM % 100) + 1 ))
echo "Random Number is $number"