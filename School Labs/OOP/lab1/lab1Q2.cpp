#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int per_hour = 40, total_hour, ot_hour, reg_hour;
    float ot_rate = 24.85, base_rate = 18.5, reg_wages, ot_wages, total_wages;

    cout<<"please enter total hours you've worked this week"<<endl;
    cin>>total_hour;

    if(total_hour>40){
        ot_hour= total_hour - reg_hour;
    }else{
        ot_hour=0;
        reg_hour=total_hour;
    }

    reg_wages= base_rate * per_hour;
    ot_wages= ot_hour * ot_rate;
    total_wages = reg_wages * ot_wages;

    cout<<"Wages for this week are RM"<<fixed<<setprecision(2)<<total_wages<<endl;
}