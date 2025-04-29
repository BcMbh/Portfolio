#include<stdio.h>

void get_min(double arr[], int size) {
    double min = arr[0]; 
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }

    printf("\nMinimum rainfall: %.2fml", min);
}

void get_max(double arr[], int size) {
    double max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    printf("\nMaximum rainfall: %.2fml", max);
}

int main() {
    double rainfall[] = {5.67, 10.9, 2.03, 12.08, 7.11}; //double rainfall[5] so no need for code below
    int size = sizeof(rainfall) / sizeof(rainfall[0]); // Calculate the size of the array

    for (int i = 0; i < size; i++) {
        printf("\nMonth %d: %.2fml", i + 1, rainfall[i]);
    }

    get_min(rainfall, size);
    get_max(rainfall, size);
}
