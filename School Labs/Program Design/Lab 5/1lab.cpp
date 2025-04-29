#include<stdio.h>

int main(){
    char product[100];
    int price;

    for (int i = 0; i < 3; i++)
    {
        printf("\nEnter Product's name:");
        scanf("%s",product);
        fflush(stdin);
        printf("\nEnter The Price:");
        scanf("%d",&price);
        fflush(stdin);
        printf("\n%s: %d", product,price);
    }

}