/*
Lab 08
Question 1
Friend classes
*/

#include <iostream>
#include <cmath>
using namespace std;
//define class
class geometry
{
	private: //private data members
		float pi, height, radius;
	public: //public member functions
		//-----(1)-----
		//parameterized constructor with two float parameters
		geometry(float hg,float rd)
		{
			pi = M_PI; height = hg; radius = rd;
		}
		//-----(2)-----
		//desctructor with display message
		~geometry()
		{
			cout<<"\n= END OF PROGRAM=";
		}
		//-----(3)-----
		//declare friend class
		friend class cylinder;
		//-----(4)-----
		//declare friend class
		friend class cone;
};
//define class
class cylinder
{
	private: //private data members
		float vol;
	public: //public member functions
		//-----(5)-----
		//calculate volume function
		void calc_vol(geometry *g) //pointer of class as parameter
		{	//calculate volume using dot and indirection operator
			vol = g->pi * g->radius * g->radius * g->height;
			//display output
			cout<<"\nVolume of cylinder with radius ";
			cout<<(*g).radius<<" and height ";
			cout<<(*g).height<<" is : "<<vol<<endl;
		}
};
//define class
class cone
{
	private: //private data members
		float vol;
	public: //public member functions
		//-----(6)-----
		//calculate volumne function
		void calc_vol(geometry &g) //reference argument of class as parameter
		{	//calculate volume using reference argument
			vol = g.pi * g.radius * g.radius * g.height/3;
			//display output
			cout<<"\nVolume of cone with radius ";
			cout<<g.radius<<" and height ";
			cout<<g.height<<" is : "<<vol<<endl;
		}
};

int main()
{	//declare variables
	float hg, rd;
	//get user input
	cout << "Enter height: ";
	cin >> hg;
	cout << "Enter radius: ";
	cin >> rd;
	//-----(7)-----
	//declare object and pass parameter values
	geometry gmt(hg,rd);
	//-----(8)-----
	//declare object
	cylinder cyc;
	//-----(9)-----
	//call method by passing object address
	cyc.calc_vol(&gmt);
	//-----(10)-----
	//declare object
	cone cn;
	//-----(11)-----
	//call method by passing object
	cn.calc_vol(gmt);
}
