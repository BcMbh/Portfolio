#include <stdio.h>
#include <string.h>


int main(){
   int day,code,ticket;
   float price;
   char movieTitle[100];

    printf("\n ----------------------------------------");
    printf("\n           Movie Title");
    printf("\n ----------------------------------------");
    printf("\n\n 1. Mission: Impossible - Fallout(RM13)");
    printf("\n 2. Ant Man and The wasp         (Rm12)");
    printf("\n ----------------------------------------");

    printf("\nEnter Movie Code:");
    scanf("%d", &code);
    printf("\nEnter number of ticket:");
    scanf(" %d", &ticket); 
    printf("\nEnter movie day(1-7):");
    scanf("%d", &day);

    if(code ==1){
        strcpy(movieTitle, "Mission: Impossible - Fallout");
        price = 13;
        price *= 0.8;

        switch (day) {
        case 6:
        case 7:
            price /= 0.8;
            break;
        default:
            break;
        }
    }else if(code ==2){
        price = 12;
        price *= 0.7; 
        strcpy(movieTitle, "Ant Man and The wasp");

        switch (day) {
        case 6:
        case 7:
            price /= 0.7;
            break;
        default:
            break;
        }
    }else{
        printf("\nInvalid Movie Code!");
        return 1;
    }

    double totalPrice = price * ticket;

    printf("\n ----------------------------------------");
    printf("\n              Receipt");
    printf("\n ----------------------------------------");
    printf("\nMovie Title: %s", movieTitle);
    printf("\nNumber of Tickets: %d", ticket);
    printf("\nTotal Price: RM%.2f\n", totalPrice);
}