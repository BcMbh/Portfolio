#include <iostream>
#include <iomanip>
using namespace std;

struct Rental
{
    char name[20];
    float rent;
    int month;
};


float report(struct Rental[]);

int main()
{
    //initialize
    struct Rental R[3]={{"Megan", 300, 4},{"Johnson", 250, 1},{"David", 790, 2}};
    float total;

    cout<<fixed<<setprecision(2);
    total = report(R); //call function
    cout<<"\nTotal rental to be collected: $"<<fixed<<setprecision(2)<<total<<endl;
}

float report(struct Rental R[])
{
    double unpaid,totalDue;

    cout<<"\n--------------------------------------";
    cout<<"\n--AMOUNT DUE MORE THAN RM1000.00---";
    cout<<"\n--------------------------------------";

    for (int i = 0; i < 3; i++)
    {
        unpaid=R[i].rent * R[i].month;

        if(unpaid >1000){
            totalDue +=unpaid;
            cout<<"\nTenan NAme\t:"<<R[i].name<<endl;
            cout<<"Tenan Rent\t:"<<R[i].rent<<endl;
            cout<<"Tenan Month\t:"<<R[i].month<<endl;
            cout<<"Tenan Due\t:"<<unpaid<<endl;
        }
    }
return totalDue;    

}