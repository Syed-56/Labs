#!/bin/bash

function factorial() {
    res=1
    for ((i=1; i<=$1; i++));    do
        ((res *= i))
    done
    echo $res
}

read -p "Input number: " num
ans=$(factorial $num) #doing $() means the echo result of function is stored in the variable
echo "Factorial of $num = $ans"