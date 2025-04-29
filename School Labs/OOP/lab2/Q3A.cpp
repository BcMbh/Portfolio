#include <iostream>
#include <iomanip>
using namespace std;

double average(int[]);
char greds(double);

struct Student
{
    char name [30];
    int marks[5];
    double avg;
    char grade;
};


int main()
{
    int i;
    struct Student S1;
    

    //inputs
    cout<<"Enter Name: ";
    cin>>S1.name;

    do
    {
        cout<<"Enter Marks: ";
        cin>>S1.marks[i];
        i++;
    } while (i <5);

    //calculate
    S1.avg = average(S1.marks);
    S1.grade = greds(S1.avg);
    
    //display
    cout<<"\nName: "<<S1.name<<endl;
    cout<<"Average: "<<fixed<<setprecision(1)<<S1.avg<<endl;
    cout<<"Grades: "<<S1.grade<<endl;

}

double average(int marks[])
{
    double total, average;

    for (int i = 0; i < 5; i++)
    {
        total += marks[i];
    }

    average = total/5;
    return average;
}

char greds(double a)
{
    char g;
    if(a>=80)
        g='A';
    else if(a>=60)
        g='B';
    else if(a>=50)
        g='C';
    else
        g='F';

    return g;
    
}