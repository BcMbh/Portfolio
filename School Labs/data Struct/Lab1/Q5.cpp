#include<iostream>
#include<iomanip>
 
using namespace std;


int i,n,av;

int main()
{

    while (i < 5)
    {
        cout<<"Enter Mark: ";
        cin>>n;
        av+=n;
        i++;
    }

    av/=5;
    cout<<"Mark average is: "<<av;
    
}