#!/bin/bash
for i in 1 2 3 4 5
do
    echo $i
done

for j in "Syed" "Sultan" "Ahmed"
do
    echo $j
done

for num in {1..10}
do
    echo $num
done

#C-style loop
for ((i=0; i<5; i++))
do
    echo "Iteration $i"
done

#while loop
count=0
num=10
while [ $count -le $num ]
do
    echo "Numbers are $count"
    let count++
done

#like C, we can use break and continue

#until loop - opposite of while
c=1
until [ $c -gt 5 ]
do 
    echo "c=$c"
    ((c++))
done

#looping through array
names=( "Sultan" "Hammad" "Ammar" "Ali" )
for individual in "${names[@]}"
do
    echo "Hello, $individual"
done

#infinite loop
# while true
# do
#     echo "Infinite"
#     sleep 2s
# done