#include <stdio.h>

float kilo[4];

void get_input(float kilo[]) {
    printf("\nEnter kilograms:\n");
    for (int i = 0; i < 4; i++) {
        scanf("%f", &kilo[i]);
        fflush(stdin);
    }
}

void convert_gram(float kilo[]) {
    printf("\nConvert Kilo to Grams:\n");
    float gram[4];
    for (int i = 0; i < 4; i++) {
        gram[i] = kilo[i] * 1000;
        printf("\nKilo: %.2f -> Grams: %.2f", kilo[i], gram[i]);
        fflush(stdin);
    }
}

void convert_pound(float kilo[]) {
    printf("\nConvert Kilo to Pounds:\n");
    float pound[4];
    for (int i = 0; i < 4; i++) {
        pound[i] = kilo[i] * 2.205;
        printf("\nKilo: %.2f -> Pounds: %.2f", kilo[i], pound[i]);
        fflush(stdin);
    }
}

int main() {
    get_input(kilo);
    convert_gram(kilo);
    convert_pound(kilo);

    return 0;
}
