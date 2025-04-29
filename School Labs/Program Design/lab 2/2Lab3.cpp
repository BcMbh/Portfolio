#include<stdio.h>

int main()
{
    const float POUND = 2.20462, INCH = 39.3701;
    float weight, height, age, BMR;

    //Input
    printf("\n Enter height(m):");
    scanf("%f", & height);
    printf("\n Enter weight(kg):");
    scanf("%f", & weight);
    printf("\n age:");
    scanf("%f", & age);


    //Pound and Inch
    weight *= POUND;
    height *= INCH;

    printf("\n Height: %.2f inches", height);
    printf("\n Weight: %.2f pounds", weight);


    //BMR
    BMR = 66 + (6.23 * weight) + (12.7 * height) - (6.8 * age);
    
    printf("\n BMR: %.2f\n", BMR);

}