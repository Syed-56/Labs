#!/bin/bash
#declaring
function myfunc {
    echo "Greetings"
}

func() {
    echo "Greetings with ()"
}

#calling
myfunc
func

#parameters: arguments are passed but not accessed in function as parameters instead we use $1, $2 for first parameter second parameterc and so on
addNums() {
    sum=$(($1+$2))
    echo "Sum is $sum"
}

addNums 10 20

#to return a result, echo it as it is and call fnuction as variable value
getSqr() {
    echo $(($1*$1))
}

square=$(getSqr 5)
echo "Square of 5 = $square"

#all variables by default are global in bash to make someone a private, use local in function
my_func() {
    local name="Secret"
    echo "Inside: $name"
}

my_func
echo "Outside: $name"