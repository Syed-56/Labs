#!/bin/bash
echo "Enter Name: "
read name
echo "Enter Favorite Colour"
read color
echo "Hello ${name}, your favorite color is ${color}"
echo ${#name}
echo ${color:0:3}
predfined=purple
if [ "$color" == "$predefined" ]
then
	echo "Purple is also my favorite color"
else
	echo "Nice, My Favorite Color is different, Its ${predefined} and not ${color}"
fi

