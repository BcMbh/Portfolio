#include <stdio.h>
#define CHOC 1.30

int main()
{
    char name[20] = "John";
    int qtty = 5;
    float totalpay;

    totalpay = qtty * CHOC;

    printf("\nChocolate price: %.2f", CHOC);
    printf("\n%s bought %d units of chocolate.\n", name, qtty);
    printf("\nTotal amount to pay: %.2f", totalpay);

    return 0;
}

