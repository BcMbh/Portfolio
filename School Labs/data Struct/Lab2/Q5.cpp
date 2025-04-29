#include <iostream>
#include <iomanip>

using namespace std;

int main() 
{
    int i,n;
    float sum, avg;
    float *p;

    cout<<"How many marks would you like to enter: ";
    cin>>i;

    p = new float [i];
    for(n=0; n<i; n++)
    {
        cout<<"Enter marks "<<n+1<<" : ";
        cin>>p[n];
    }

    cout<<"You have entered: ";
    for(n=0; n<i; n++)
    {
        if (i<5)
            cout<<p[n]<<", ";
        else
        cout<<p[n];

        sum+=p[n];
    }

    cout<<"\nSum of mark is: "<<sum;
    
    avg = sum/sizeof(p);
    cout<<"\nAverage mark is: "<<avg;

    

    return 0;
}