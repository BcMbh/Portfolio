#include<iostream>
 
using namespace std;

struct employee
{
    string first_name, last_name, emp_num;
    int age;
};


int main()
{
    employee record;

    cout<<"First Name: ";
    cin>>record.first_name;
    cout<<"Last name: ";
    cin>>record.last_name;
    cout<<"Employee Number: ";
    cin>>record.emp_num;
    cout<<"Age: ";
    cin>>record.age;

    cout<<"\n\nHello "<<record.first_name<<" "<<record.last_name
    <<"\nYour employeee number "<<record.emp_num
    <<"\nYou are "<<record.age<<" years old";
}