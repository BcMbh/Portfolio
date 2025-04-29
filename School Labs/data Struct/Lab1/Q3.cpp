#include<iostream>
#include<iomanip>
#include <string>
 
using namespace std;

char op;
int n1,n2,total;

int main()
{
    cout<<"Enter an Operator(+,-,*,/): \n";
    cin>>op;

    switch(op){
    case '+':
        cout<<"Enter two operands:";
        cin>>n1>>n2;
        total=n1+n2;
        cout<<n1<<"+"<<n2<<"="<<total;
        break;
    case '-':
        cout<<"Enter two operands:";
        cin>>n1>>n2;
        total=n1-n2;
        cout<<n1<<"-"<<n2<<"="<<total;
        break;
    case '*':
        cout<<"Enter two operands:";
        cin>>n1>>n2;
        total=n1*n2;
        cout<<n1<<"*"<<n2<<"="<<total;
        break;
    case '/':
        cout<<"Enter two operands:";
        cin>>n1>>n2;
        total=n1/n2;
        cout<<n1<<"/"<<n2<<"="<<total;
        break;
    }
}