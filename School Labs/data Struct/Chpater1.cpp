#include<iostream>
 
using namespace std;

int main()
{
 int a[4] = {2,4,6};
 int *ptr, x=10, y=20, i;
 ptr = a;
 ptr[2] = x + (*ptr+1);
 *ptr = y++;
 int &z= x;
 z = y + 2;
 ptr = a;
 *(ptr + 3) = *ptr + 2;
 for(i = 0; i<4; i++)
 cout<<a[i]<<" ";
 cout<<endl;
 cout<<x<<" "<<y<<" "<<z<<" "<<endl;
}