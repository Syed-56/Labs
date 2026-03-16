#!/bin/bash

for i in {1..10}
do
	echo -n "$i "
done
echo

for word in $(head -3 practice.sh); do
	echo -n "$word "
done
echo

k=10
while [ $k -gt 0 ]; do
	echo -n "$k "
	((k--))
done
echo 

j=1
until [ $j -gt 6 ]; do
	echo -n "$j "
	((j++))
done
echo