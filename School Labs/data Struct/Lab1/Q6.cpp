#include<iostream>
 
using namespace std;

int n[5]={1,2,3,4,5};
int Sum(int n[]);

int main()
{
    int n[5]={1,2,3,4,5};
    int sum;

    cout<<"Enter five numbers and the program will calculate sum of the numbers.\n";
    for (int i = 1; i <= 5; i++)
    {
        cout<<"Enter number "<<i<<": ";
        cin>>n[i];
    }

    cout<<"You have entered : ";
    for (int i = 1; i <= 5; i++)
    {
        if (i<5)
            cout<<n[i]<<", ";
        else
        cout<<n[i];
    }

    sum = Sum(n);

    cout<<"\nSum of the numbers entered is : "<<sum;
       
}

int Sum(int n[])
{
    int sum=0;
    for (int i = 0; i < 5; i++)
    {
        sum +=n[i];
    }
    
    return sum;
}