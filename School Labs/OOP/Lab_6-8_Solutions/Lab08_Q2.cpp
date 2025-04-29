/*
Lab 08
Question 2
Adding friend class
*/

#include <iostream>
#include <cmath>
using namespace std;
//define class
class geometry
{
	private: //private data members
		float pi, height, radius, length; //add length parameter
	public: //public member functions
		//parameterized constructor with three float parameters
		geometry(float hg,float rd, float lg)
		{
			pi = M_PI; height = hg; radius = rd; 
			length = lg;
		}
		//desctructor with display message
		~geometry()
		{
			cout<<"\n= END OF PROGRAM=";
		}
		//declare friend classes
		friend class cylinder;
		friend class cone;
		//declare new friend class
		friend class cube;
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
//define class
class cube
{
	private: //private data members
		float vol;
	public: //public member functions
		//calculate volume function
		void calc_vol(geometry &g) //reference argument of class as parameter
		{	//calculate volume using reference argument
			vol = g.length * g.length * g.length;
			//display output
			cout<<"\nVolume of cube with length ";
			cout<<g.length<<" is : "<<vol<<endl;
		}
};

int main()
{	//declare variables
	float hg, rd, lg;
	//get user input
	cout << "Enter height: ";
	cin >> hg;
	cout << "Enter radius: ";
	cin >> rd;
	//add prompt for user to enter length
	cout << "Enter length: ";
	cin >> lg;
	//declare object and pass parameter values
	geometry gmt(hg,rd,lg);
	//declare object
	cylinder cyc;
	//call method by passing object address
	cyc.calc_vol(&gmt);
	//declare object
	cone cn;
	//call method by passing object
	cn.calc_vol(gmt);
	//add declaration and method call for new class object
	cube cb; //declare object
	cb.calc_vol(gmt); //call method by passing object
}
