#include <stdio.h>
#include "speed.h"

int main() {
    float speed;
    printf("Enter Speed in metre/sec: ");
    scanf("%f", &speed);
    float kmh = convertSpeed(speed);
    printf("Speed kmh: %f", kmh);
}