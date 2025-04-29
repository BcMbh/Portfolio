/*
Lab 11
Question 2
Public class inheritance and repetition
*/
 
#include<iostream>
#include<cmath>
using namespace std;
//define class
class Triangle
{
	protected: //protected data members
		int a, b, c;
	public: //public member functions
		Triangle() //default constructor
		{
			cout<<"-------- Triangle Class -------\n";
		}
		void setData(int in_a, int in_b)
		{ //mutator function
			a = in_a;
			b = in_b;
		}
};
//define class that ineherits another publicly
class PythagorasTriangle:public Triangle
{
	public: //public member functions
		PythagorasTriangle() //default constructor
		{
			cout<<"-------Pythogoras Triangle -------\n";
		}
		void calcHypotenuse()
		{ 	//function to calculate hypotenuse
			c = sqrt(pow(a,2)+pow(b,2));
		}
		void displaySides()
		{	//display values of data members
			cout<<"\n::The sides of a Pythagoras triangle::\n";
			cout<<"a : "<<a<<endl;
			cout<<"b : "<<b<<endl;
			cout<<"c : "<<c<<" (also known as the Hypotenuse)\n"<<endl;
		}
};
 
int main()
{
	int var_a, var_b;
	char in;
	//loop to repeat as user require
	do{	//declare dynamic class object
		PythagorasTriangle *pt = new PythagorasTriangle;
		//prompt user to enter values for side
		cout<<"Enter a : ";
		cin>>var_a;
		cout<<"Enter b : ";
		cin>>var_b;
		//call mutator function to set values to object
		pt->setData(var_a,var_b);
		//call method to calculate hypotenuse
		pt->calcHypotenuse();
		//call method to display values of triangle
		pt->displaySides();
		//delete dynamic object
		delete pt;
		//prompt user decision
		cout<<"Do you want to continue [Y/N]: ";
		cin>>in;
		cout<<endl;
	}while(in=='Y'); //condition to continue
}