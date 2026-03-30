#!/bin/bash
var=10+5
echo $var   #bash treat all data as string

#to tell bash that its math, use let
let mathVar=10+10-3
echo $mathVar

#to use arithmetic operators, close them in (()). dont use it on let variables
echo $mathVar
((a=10*5))
((a+=3))
echo $a

math=80
phy=90
echo "Total: $((math + phy))"
weightedScore = $((math*phy))
echo "Weighted: $weightedScore"
#division not allowed in bash, for it we use bc which is not part of course.