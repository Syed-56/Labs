const students = [
    { name: "Ali", age: 20, grade: 80 },
    { name: "Sara", age: 22, grade: 90 },
    { name: "Ahmed", age: 19, grade: 90 }
];
for(let i=0; i<3; i++) {
    console.log("Student ",i+1);
    console.log("Name : ",students[i].name);
    console.log("Age : ",students[i].age);
    console.log("Grade : ",students[i].grade);
}
for(let i=0; i<3; i++) {
    for(let j=0; j<3-1-i; j++) {
        if(students[j].grade > students[j+1].grade) {
            const temp = students[j];
            students[j] = students[j+1];
            students[j+1] = temp;
        }
    }
}
for(let i=0; i<3; i++) {
    console.log("Student ",i+1);
    console.log("Name : ",students[i].name);
    console.log("Age : ",students[i].age);
    console.log("Grade : ",students[i].grade);
}