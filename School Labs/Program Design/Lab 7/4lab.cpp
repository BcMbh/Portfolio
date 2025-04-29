#include <stdio.h>

int main() {
    float rate[4][5] = {{2.30, 4, 5}, {3, 2.1, 1, 4}, {1, 2, 3, 4, 5}, {4, 2}};
    double average;

    printf("Average rating for each product\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < 4; i++) {
        average = 0; // Reset 

        for (int j = 0; j < 5; j++) {
            average += rate[i][j];
        }

        average /= 5; 

        printf("Product %d: %.2f\n", i + 1, average);
    }

    return 0;
}
