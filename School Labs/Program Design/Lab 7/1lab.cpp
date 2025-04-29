#include<stdio.h>
#define convert 2.54

int main(){
    int cm[5], inch[5];
    int total;

    for (int i = 0; i < 5; i++)
    {
        printf("\nEnter The Inches:");
        scanf("%d",&inch[i]);
        cm[i] = inch[i] * convert;
        fflush(stdin);
    }

    printf("\nHere are the results of the conversion");
    printf("\n ----------------------------------------");
    for (int i = 0; i < 5; i++) {
        printf("\nInches: %d -> Centimeters: %d", inch[i], cm[i]);
    }

}