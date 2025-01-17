#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to move the tortoise based on the random number
int moveTortoise() {
    int i = rand() % 10 + 1; // Random number between 1 and 10
    if (i >= 1 && i <= 5) {
        return 3; // Fast plod
    } else if (i >= 6 && i <= 7) {
        return -6; // Slip
    } else {
        return 1; // Slow plod
    }
}

// Function to move the hare based on the random number
int moveHare() {
    int i = rand() % 10 + 1; // Random number between 1 and 10
    if (i >= 1 && i <= 2) {
        return 0; // Sleep
    } else if (i >= 3 && i <= 4) {
        return 9; // Big hop
    } else if (i == 5) {
        return -12; // Big slip
    } else if (i >= 6 && i <= 7) {
        return 1; // Small hop
    } else {
        return -2; // Small slip
    }
}

void printRace(int tortoise, int hare) {
    for (int i = 1; i <= 70; i++) {
        if (i == tortoise && i == hare) {
            printf("OUCH!!!");
            i += 6; // Skip printing after OUCH!!!
        } else if (i == tortoise) {
            printf("T");
        } else if (i == hare) {
            printf("H");
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    srand(time(0)); // Seed the random number generator with current time

    int tortoise = 1;  // Starting position of the tortoise
    int hare = 1;      // Starting position of the hare
    int tick = 0;
    printf("BANG !!!!!\nAND THEY'RE OFF !!!!!\n");
    // Simulate the race
    while (tortoise < 70 && hare < 70) {
        // Move the animals
        tortoise += moveTortoise();
        hare += moveHare();
        // Ensure animals do not move before square 1
        if (tortoise < 1) tortoise = 1;
        if (hare < 1) hare = 1;
        // Print the race status
        printRace(tortoise, hare);
        // Check if either animal has reached or passed square 70
        if (tortoise >= 70 && hare >= 70) {
            printf("It's a tie!\n");
            break;
        } else if (tortoise >= 70) {
            printf("TORTOISE WINS!!! YAY!!!\n");
            break;
        } else if (hare >= 70) {
            printf("Hare wins. Yuch.\n");
            break;
        }
        // Simulate the passage of time (tick)
        tick++;
    }
    return 0;
}