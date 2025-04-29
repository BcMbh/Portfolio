#include<stdio.h>

int x=337;

void Q(int z)
{
    z += x;
    void print(int z);
}
void P(int *y)
{
    int x = *y + 8;
    Q(x);
    *y = x - 3 * x;
    void print(int x);
}
void print(int val)
{
    printf("\n%d", val);
}

int main()
{
    x = 5;
    P(&x);
    print(x);
}