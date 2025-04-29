#include <stdio.h>
#define IRON_COST 5

int main() {
    float weight, payment, rate;
    char decision;

    printf("\n --------------------------");
    printf("\n  Welcome to Clean Laundry");
    printf("\n --------------------------");

    printf("\nLaundry weight:");
    scanf("%f", &weight);
    printf("\nNeed Ironing [Y/N]? :");
    scanf(" %c", &decision); 

    // Ironing?
    if (decision == 'Y' || decision == 'y') {
        if (weight < 5) {
            rate = 1;
        } else if (weight >= 5 && weight < 10) {
            rate = 1.5;
        } else if (weight >= 10 && weight < 15) {
            rate = 2;
        } else {
            rate = 2.5;
        }

        // Add the ironing cost
        payment += rate + IRON_COST;

    } else if (decision == 'N' || decision == 'n') {
        printf("Thank You for the money.\n");
    } else {
        printf("Invalid input for ironing decision.\n");
    }
    
    //Bill
    printf("\n Your Bill");
    printf("\n---------");
    printf("\n Weight: %.2f",weight);
    printf("\n Rate:%.2f", rate);
    printf("\n Iron:%c (%d)",decision,IRON_COST);
    printf("\nBill: %.2f", payment);

    return 0;
}
