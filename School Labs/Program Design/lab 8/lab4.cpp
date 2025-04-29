#include<stdio.h>

int main(){
    int numbers[]={10,8,34,100,3,12,14,7};
    int *a, *b;
    a = &numbers[3];
    b = numbers;
    printf("\n %d", *a + *b);
    printf("\n %d", *a-- - ++*b);
    printf("\n %d", *(a+2) + *b+15);
}