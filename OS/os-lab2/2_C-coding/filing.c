#include <stdio.h>

int main() {
    //1. Declare File ptr
    FILE* fptr;

    //2. Open File in a mode
    fptr = fopen("data.txt","w");   //a is append mode and r is read mode. also adding + after any mode means update mode too

    //3. Always Check null
    if(!fptr) {
        printf("Error Opening File\n");
        return 1;
    }

    //4. To write in a file instead of console, use fprintf
    fprintf(fptr, "ID: %d, Name: %s", 101, "Gemini");

    //5. Close file
    fclose(fptr);

    //Now we can use fscanf to read from file just like scanf read from console
    int id;
    char name[20];
    fptr = fopen("data.txt","r");
    //also fscanf returns EOF when file ends
    while(fscanf(fptr, "ID: %d, Name: %s\n", &id, name) != EOF) {
        printf("Read From File --> Name: %s and ID: %d\n", name, id);
    }
    fclose(fptr);
    return 0;
}