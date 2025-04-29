#include<iostream>
#include<iomanip>
using namespace std;

class Rice
{ 
    float price_per_kg, total_weight;

    public:
    Rice(float w)
    { 
        price_per_kg = 10.0;
        total_weight = w;
    }

    void display_rice()
    { 
        cout<<"----------------------------------------"<<endl;
        cout<<"\tRice Details"<<endl;
        cout<<fixed<<setprecision(2);
        cout<<"Total weight\t : "<<total_weight<<endl;
        cout<<"Price perkg (RM): "<<price_per_kg<<endl;
        cout<<"Total (RM)\t : "<<total_weight*price_per_kg<<endl;
    }
}; 

class Product{
    float kg;

    public: //overload addition operator taht create new rice object
    Rice operator+(const Product &P){//constant refrence to product object
        return Rice(kg+P.kg);
    }
    void setData(){
        cout<<"Enter product weight(kg): ";
        cin>>kg;
    }
    
};

int main()
{
    Product a,b;
    a.setData();
    b.setData();
    //this wil call operator class function defined in the product class to createa new rice object with the combined weight
    Rice h=a+b;
    h.display_rice();

    return 0;
}