#include<stdio.h>

int main() {
    char name[100], again;
    int donate, total, frequency;

    printf("\nDonate[Y]: ");
    scanf(" %c", &again); // Notice the address-of operator before 'again'

    while (again == 'Y') {
        printf("\nEnter Client: ");
        scanf("%s", name);

        printf("\nEnter Frequency: ");
        scanf("%d", &frequency);

        for (int i = 0; i < frequency; i++) {
            printf("\nEnter amount: ");
            scanf("%d", &donate);
            total += donate; 
        }
        printf("\n Total Donation from %s: RM %d", name, total);
        printf("\nDonate[Y]: ");
        scanf(" %c", &again); 
    }

    printf("\nTotal donation: %d\n", total);

    return 0;
}
