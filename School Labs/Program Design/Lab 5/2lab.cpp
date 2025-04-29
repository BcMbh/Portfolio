#include<stdio.h>


int main(){
    char name[100],id[100];
    int fee,year;

    printf("\nEnter Name:");
    scanf("%s",name);
    printf("\nEnter ID");
    scanf("%s",id);
    printf("\nFee(RM):");
    scanf("%d",&fee);
    printf("\nEnter duration of years(RM)");
    scanf("%d",&year);
    

    printf("\n ----------------------------------------");
    printf("\n           MMU");
    printf("\n ----------------------------------------");
    printf("\nEnter Name: %s",name);
    printf("\nEnter ID: %s",id);
    printf("\nFee(RM): %d", fee);
    printf("\nEnter duration of years(RM): %d", year);

    printf("\nYear-----Course Fee");
    int i = 1;
    do{
        printf("\n%d ----- RM %d", i, fee);
        fee += fee * 0.05; 
        i++;
    }while (i <= year);
    
}