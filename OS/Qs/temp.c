#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    int num1=10, num2=2, num3=7;
    FILE* fptr = open("data.txt","w");
    fprintf(fptr, "%d %%d %d", num1,num2,num3);

    //sequential forking
}
