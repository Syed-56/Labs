#include <stdio.h>

int add(int x, int y) {
    return x+y;
}

void greet(char name[]) {
    printf("Greetings %s\n", name);
}

void printArr(int arr[], int size) {
    for(int i=0; i<size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    printf("%d\n", add(2,3));
    greet("Sultan");
    int arr[] = {1,2,3,5};
    printArr(arr,4);
}