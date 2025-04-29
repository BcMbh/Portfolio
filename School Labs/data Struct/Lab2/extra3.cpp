#include <iostream>
#include <iomanip>

using namespace std;

int main() 
{
    int *a,*b,*c,d,e;
    a=&d;
    *a = 3+10;
    b=&e;
    *b=*a+3;
    c=b;
    d=*c + *a;
    *c=*a+e;
    cout<<*a<<" "<<*b<<" "<<*c<<" "<<d<<" "<<e; 
}