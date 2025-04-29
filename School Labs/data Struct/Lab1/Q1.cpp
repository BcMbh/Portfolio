#include<iostream>
#include<iomanip>
 
using namespace std;

int n1,n2,n3,n4,high;
 
int main()
{
    	cout<<"Enter four integers: ";
        cin>>n1;
        if(high < n1)
            high=n1;
        
        cin>>n2;
        if(high < n2)
            high=n2;
        
        cin>>n3;
        if(high < n3)
            high=n3;
        
        cin>>n4;
        if(high < n4)
            high=n4;
        

        cout<<"Maximum Number: "<<high;

}