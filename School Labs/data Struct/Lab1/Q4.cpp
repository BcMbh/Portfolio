#include<iostream>
#include<iomanip>
 
using namespace std;

int main()
{
    for (int i = 0; i <= 5; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cout<<j;
        }
        cout<<""<<endl;
    }
    
}