/*
Lab 07
Question 1(a)
Copy constructor
*/

#include<iostream>
using namespace std;
//define class
class Bags
{	//private data members
	string brand;
	float height, length, width;
	public: //public member functions
		void setdata() //mutator function to get user input
		{
			cout<<"Enter your bag's brand name : ";
			getline(cin, brand);
			cout<<"Enter value length , width and height of your bag L, W, H ";
			cin>>length>>width>>height;
		}
		void display() //showing data members
		{
			cout<<"\nYour brand bag name is **"<<brand<<"** and the dimensions are: "
			<<length<<"L "<<width<<"W "<<height<<"H "<<endl;
		}
		Bags (const Bags &Bi) //copy constructor
		{
			brand = Bi.brand;
			length = Bi.length;
			width = Bi.width;
			height = Bi.height;
			cout<<"\nDo you have the same bag??"<<endl;
		}
		Bags() //default constructor
		{
			brand = "Adidas";
			length = 35;
			width = 20;
			height = 45;
		}
};
int main()
{ 	//need to developed by adding object K, L and M;
	Bags K; //declare object
	//call object member functions
	K.setdata();
	K.display();
	
	Bags L; //declare object
	//call object member function
	L.display();
	
	//declare object as copy of another object
	Bags M(L); // or M = L;
	//call object member function
	M.display();
	
	//observation: 	First object stores data entered by user, second object initialized by default constructor
	//				Third object initialized by copying from another existing object, constructor initialization
	//				indicated by "same bag?" message and contains same data as copied object
}
