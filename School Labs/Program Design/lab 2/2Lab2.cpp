#include <stdio.h>
#define PI 3.142

int main() {
    float radius, time, circular_velocity;

    printf("\nEnter radius (cm) :");
    scanf("%f", &radius);
    printf("Enter time (s) :");
    scanf("%f", &time);

    circular_velocity = (2 * PI * radius) / time;

    printf("\nRadius: %.2f cm", radius);
    printf("\nTime: %.2f seconds", time);
    printf("\nCircular Velocity: %.2f cm/s\n", circular_velocity);

    return 0;
}

