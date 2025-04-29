#include<iostream>
#include<iomanip>
 
using namespace std;

int n=1;

int main()
{
    while(n!=0)
    {
        cout<<"Type a number (0 to exit): ";
        cin>>n;
        
        if(n==0)
            break;
        else if(n %2 ==0)
            cout << n << " is even.\n";
        else
            cout << n << " is odd.\n";

        //(n % 2 == 0) ? cout << n << " is even.\n" :  cout << n << " is odd.\n";
    }

    cout<<"Thank You. ";
    
}