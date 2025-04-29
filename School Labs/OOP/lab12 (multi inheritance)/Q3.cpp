#include <iostream>
#include <iomanip>
using namespace std;
 
//base/parent class 1
class Player
{
    protected:
        string id,name;
    public:
    void setdetails()
    {
        cin.ignore();
        cout<<"\nEnter ID : ";
        cin>>id;
        cout<<"Enter Name : ";
        cin>>name;
    }
};

//base/parent class 2
class progress
{
    protected:
        float point[3], average;
    public:
        void mark_entry()
        {
            float total;
            for (int i = 0; i < 3; i++)
            {
                cout<<"Enter round"<<i+1<<"points : ";
                cin>>point[i];
                total +=point[i];
            }
            average=total/3;
        }
};

//derive/child class, inherited form many base/parent class
class Result:public Player, public progress
{
    public:
    void display()
    {
        cout<<"Id : "<<id<<endl;
        cout<<"Name : "<<name<<endl;
        cout<<"Average point : "<<fixed<<setprecision(2)<<average<<endl;
        cout<<endl;
    }

    friend void summary(Result[], int);
};
void summary(Result obj[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout<<"player ID"<<obj[i].id<<"is a ";
        if(obj[i].average>2){
            cout<<"Gold Player"<<endl;
        }else if (obj[i].average>1.5)
        {
           cout<<"Silver Player"<<endl;
        }else
            cout<<"Bronze Player"<<endl;
    }
    
}

int main() {
    int numPlayer;
    cout<<"Enter Number of Player: ";
    cin>>numPlayer;
    Result *p = new Result[numPlayer];

    for (int i = 0; i < numPlayer; i++)
    {
        (p+i)->setdetails();
        (p+i)->mark_entry();
    }
    cout<<"--------------Game Result--------------------"<<endl;
    for (int i = 0; i < 2; i++)
    {
        cout<<"Player #"<<i+1<<endl;
        (p+1)-> display();
    }
    summary(p,numPlayer);
    delete []p;
}