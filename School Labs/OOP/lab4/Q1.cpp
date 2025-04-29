#include<iostream>
using namespace std;
class Fraction
{ 
//--------(i)---------
//private data member 
private:
	int denom, nume;
//public member function
public:
	//function set the nume and denom
	void setData(int a, int b)
	{
		nume=a;
		denom=b;
	}
	//accessor function
	int getDenom()
	{
		return denom;
	}
	int getNume()
	{
		return nume;
	}
};

int isValid(Fraction ob)
{ 
    int valid;
    if (ob.getDenom()==0){
        valid = 0;
    cout<<"\nAlert: Denominator is having value zero "<<endl;
    } 
    else if (ob.getNume()>ob.getDenom()){
        valid = 0;
    cout<<"\nAlert: Numerator greater than denominator"<<endl;
    }
    else
        valid = 1;
    return valid;
}

int main()
{ 
    Fraction ob1[3]; //declare fraction class array object
    int x,y,check;
    for(int i=0; i<3; i++){
        ob1[i].setData(i+1,2-i);
        //--------(ii)----------
        //call accessor functions to get data
        x=ob1[i].getNume();
        y=ob1[i].getDenom();
        cout<<"\nFraction "<<x<<"/"<<y;
        check=isValid(ob1[i]);//check the validity in each object of array
        if (check==1)
            cout<<" is valid"<<endl;
            else
            cout<<" is invalid"<<endl;
        }
    return 0;
}