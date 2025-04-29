#include <stdio.h>
#include <string.h>


int main(){
   int code,adult,child;
   float Aprice,Cprice;
   char Destination[100], ReturnTicket[1];

    printf("\n ----------------------------------------");
    printf("\n           Destination");
    printf("\n ----------------------------------------");
    printf("\n\n 1. Penang                       (RM13)");
    printf("\n 2. Kelantan                     (Rm12)");
    printf("\n 3. Perlis                       (Rm12)");
    printf("\n ----------------------------------------");

    printf("\nEnter Ticket[Y/N]:");
    scanf("%c", &ReturnTicket);
    printf("\nEnter Destination Code:");
    scanf("%d", &code);
    printf("\nEnter Adult:");
    scanf(" %d", &adult); 
    printf("\nEnter Child:");
    scanf(" %d", &child); 

    //soo repetitive, what do i learn from this

    printf("\n ----------------------------------------");
    printf("\n              Receipt");
    printf("\n ----------------------------------------");
    printf("\nMovie Title: %s", Destination);
}