#!/bin/bash
marks=50

#after if, write [ condition ] and in next line write then, after it write your instructions then else then instructions and close it by fi
#you can also use else if concept by writing elif [ condition ] followed by a then
if [ $marks -gt 40 ]
then
    echo "Passed"
elif [ $marks -eq 40 ]
then
    echo "Draw"
else
    echo "Failed"
fi

#bash dont have >,< or == etc. -gt is greater, -lt is less than/ -ge and -le are greater than equal to and less than equal to.
color="Purple"
predefined="Black"
if [ $color != $predefined ]
then
    echo "Your color choice is poor"
else
    echo ""
fi
#for math comparison, we use -eq for == and -ne for != but for string we use the symbols

#Logical Operators
#same we can use || and && but for it use double bracker [[]]
age=18
iq=100
if [[ $age -ge 18 && $iq -gt 100 ]]
then
    echo "You can Vote"
else
    echo "No voting"
fi