#include <stdio.h>
#include <string.h>

int main() {
    // Variables
    char room_type, room_choice[20], name[20]; 
    int days, price, Bill;

    printf("\n --------------------------");
    printf("\n  Welcome to Legend Hotel");
    printf("\n --------------------------");
    printf("\n\nroom_types: Deluxe(1 or D) Twin Sharing(2 or T) Single(3 or S)");

    // Input
    printf("\n Enter Your Name: ");
    scanf(" %[^\n]", name); // Use a space before % to consume leading whitespace and [^\n] to read until a newline
    printf("\nEnter room_type Code: ");
    scanf(" %s", &room_type); 
    printf("\nEnter Number of Days: ");
    scanf("%d", &days); 

    // Switch statement
    switch(room_type) {
        case '1':
        case 'D':
            strcpy(room_choice, "Deluxe");
            price = 200;
            break;

        case '2':
        case 'T':
            strcpy(room_choice, "Twin Sharing");
            price = 170;
            break;

        case '3':
        case 'S':
            strcpy(room_choice, "Single");
            price = 120;
            break;

        default:
            printf("\n Invalid room_type code.\n");
    }

    Bill = price * days;

    //output
    printf("\n --------------------------");
    printf("\n     Payment Reciept");
    printf("\n --------------------------");
    printf("\nCutomer Name: %s", name);
    printf("\nRoom Type: %s", room_choice);
    printf("\nRoom Price: RM%d", price);
    printf("\nNumber of Days: %d",days);
    printf("\nBill: RM%d",Bill);

    return 0;
}
