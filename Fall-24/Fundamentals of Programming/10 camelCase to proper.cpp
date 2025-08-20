#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    char *str = (char*) malloc(50 * sizeof(char));
    if (!str) exit(1);

    printf("Enter String: ");
    fgets(str, 50, stdin);
    str[strcspn(str, "\n")] = 0; // Remove the newline character

    int n = strlen(str);
    
    // Allocate extra space for potential spaces before uppercase letters
    char *result = (char*) malloc((2 * n) * sizeof(char)); 
    if (!result) exit(1);

    int j = 0;
    for (int i = 0; i < n; i++) {
        // Insert space before uppercase letters except at the start of the string
        if (str[i] >= 'A' && str[i] <= 'Z' && i != 0) {
            result[j++] = ' '; // Add space
        }
        result[j++] = str[i]; // Copy the current character
    }
    result[j] = '\0'; // Null-terminate the new string

    printf("Modified String: ");
    puts(result);

    // Free the allocated memory
    free(str);
    free(result);
    
    return 0;
}