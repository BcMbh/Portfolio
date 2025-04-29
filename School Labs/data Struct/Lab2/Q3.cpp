#include <iostream>
#include <iomanip>

using namespace std;

class BMI
{
private:
    float height,weight,bmi;
public:
    BMI() : height(1.0), weight(1.0), bmi(0.0) {}

    void set(float h, float w){
        height=h;
        weight=w;
    }

    void claculate(){
        bmi=weight/(height*height);
    }

    void display(){
        cout<<"Your bmi is :"<<bmi<<endl;
        if (bmi<18.5)
            cout<<"You are Underweight";
        else if (bmi<24.9)
            cout<<"You are Normal";
        else if(bmi<29.9)
            cout<<"You are Overweight";
        else
            cout<<"You are Obese";
    }
};



int main() 
{
    float height,weight;

    cout<<"This program will calculate your body mass index.\n";
    cout<<"Enter your height in meter (m) unit : ";
    cin>>height;
    cout<<"Enter your weight in kilogram (kg) unit : ";
    cin>>weight;

    BMI bmi;
    bmi.set(height,weight);

    bmi.claculate();
    bmi.display();
}