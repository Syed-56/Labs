console.log("Hello World");
//VARIABLE DATATYPE
var nam = "John";
console.log(nam);
var nam = "Johnny";
console.log(nam);
let aalo = 10;
console.log(aalo);
// let aalo = 20;
// console.log(aalo);
// var can be declared again but let cant
age = 25;
console.log(age);
var age; 
let greeting =  "Hello";
//if else
if (age = 25) {
    console.log(greeting);
} else {
    console.log(No);
}
//var can be declared and assigned again
// let cant be declared but cant be assigned again
// const cant be declared and assigned again
//let or var can be declared later after initializationt but const cant
const pi = 3.124;
console.log(pi);
// pi = 3.142;
// console.log(pi);  ERROR
//variable cant start with a number

//object
let person = {
    name: "John",
    age: 30
};
console.log(person.name);
console.log(person.age);

//arrays
let numbers = [1, 2, 3, 4];
console.log(numbers[2]);
let mixedarray = [1, "hello", true, {key: "value"} ]
for (let i = 0; i <= 3; i++) {
    console.log(mixedarray[i])
}

//functions
let naam;
naam = "Syed";
function greet(name) {
    return "Hello " + name;
}
let hi = greet(naam);
console.log(hi);

function hello() {
    console.log("Hello World");
}
hello();
console.log("Log");

//push and splice
let arr = ["apple", 1, "banana"];
console.log(arr);
arr.push(2,"cake"); //push dont see index and always put things at end so 2 and cake are inserted
console.log(arr);
arr.splice(2,2); //remove 2 elements starting from index 2
console.log(arr);
arr.splice(1,1,"Hi"); //replaces 1 element starting from index 1
console.log(arr);
arr.splice(1,0,true,4); //adds 2 elements from index 1 
console.log(arr);