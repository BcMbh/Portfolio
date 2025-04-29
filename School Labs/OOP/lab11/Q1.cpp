#include <iostream>
#include <cmath>
using namespace std;

//base / parent class
class Triangle
{
    protected:
    int a, b, c;
    public:
    Triangle(){ //default constructor
        cout<<"-----------Triangle Class -------------\n";
    }
    void setData(int in_a, int in_b){ //mutator
        a= in_a;
        b= in_b;
    }
};

//define class inherit publicly/derived/child class
class PythagorasTriangle:public Triangle{
    public:
    PythagorasTriangle(){ //default constructor
        cout<<"-----------PyhtagorasTruangle Class -------------\n";
    }
    void calcHypotenuse(){
        c= sqrt(pow(a,2) + pow(b,2));
    }
    void displaySides(){
        cout<<"\n::The sides of a Pythagoras Triangle::\n";
        cout<<"a: "<<a<<endl;
        cout<<"b: "<<b<<endl;
        cout<<"c: "<<c<<endl;
    }
};

int main()
{
    PythagorasTriangle *pt = new PythagorasTriangle;
    int var_a, var_b;

    cout<<"\n Cout a:";
    cin>>var_a;
    cout<<"\n Cout b:";
    cin>>var_b;

    pt->setData(var_a,var_b);
    pt->calcHypotenuse();
    pt->displaySides();

    delete pt;
}