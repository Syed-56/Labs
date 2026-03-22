#include <stdio.h>
#include <stdbool.h>

int main() {
    //datatypes and variables
    printf("Hello World\n");
    int age=18;
    float marks;
    scanf("%f", &marks);
    printf("Marks: %.2f and Age: %d\n", marks, age);
    
    //operations
    int a=5,b=10;
    int sum = a+b;
    int diff = 10-sum;
    diff++;
    printf("Sum: %d and Diff: %d\n", sum, diff);

    //if-else
    int number=18;
    if(number>18) printf("Plz vote");
    else if(number==18)    printf("Create NIC then vote");\
    else    printf("Dont vote");
    printf("\n");

    int day = 2;
    switch (day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        default:
            printf("Invalid day\n");
    }

    //boolean
    bool boolean = true;
    if((age>18 && day==2) || !(boolean)) {
        printf("Either is true\n");
    }

    //loops
    for(int i=0; i<10; i++) {
        printf("i=%d\t",i);
    }

    bool sultanGraet=true;
    while(sultanGraet) {
        printf("\nSultan is Best\n");
        sultanGraet = !sultanGraet;
    }
}