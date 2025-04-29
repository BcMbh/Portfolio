#include<stdio.h>
#define white 0.05
#define green 0.10
#define pink 0.15

int main()
{
    int Q_White, Q_Green, Q_Pink;
    float TWhite, TGreen, TPink;

    //input
    printf("\n Quantity of WHite A4:");
    scanf("%i", & Q_White);
    printf("\n Quantity of Green A4:");
    scanf("%i", &Q_Green);
    printf("\n Quantity of Pink: A4");
    scanf("%i", & Q_Pink);

    //count
    TWhite = white * Q_White;
    TGreen = green * Q_Green;
    TPink = pink *Q_Pink;

    //Print
    printf("\n White A4 Paper: RM%f (%i X %.2f)\n", TWhite, Q_White, white);
    printf("\n Green A4 Paper: RM%f (%i X %.2f)\n", TGreen, Q_Green, green);
    printf("\n Pink A4 Paper: RM%f (%i X %.2f)\n", TPink, Q_Pink, pink);

    return 0;

}
