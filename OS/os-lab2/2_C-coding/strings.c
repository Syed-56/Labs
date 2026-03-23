#include <stdio.h>
#include <string.h>

void printNames(char strs[][50], int count) {
    for(int i=0; i<count; i++)  printf("%s\n", strs[i]);
}

int main() {
    char name[50] = "Gemini";
    char input[50];
    printf("Hello, %s\n", name);
    printf("Enter Name: ");
    fgets(input,sizeof(input),stdin);
    printf("Hello: %s\n", input);

    if (strcmp(name,input)==0)  printf("Wow same");
    else    printf("Not same");
    printf("\n");
    strcpy(name,"Claude");
    strcat(name,"-code");
    printf("New NAme: %s\n with letters = %ld\n", name, strlen(name));
    char arrStrs[3][50] = {"Syed", "Sultan", "Ahmed"};
    printNames(arrStrs,3);
}