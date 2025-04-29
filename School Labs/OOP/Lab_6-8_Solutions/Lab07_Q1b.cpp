/*
Lab 07
Question 1(b)
Friend function
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
		{   cout<<"Enter your bag's brand name : ";
			getline(cin, brand);
			cout<<"Enter value length , width and height of your bag L, W, H ";
			cin>>length>>width>>height;
			//fflush(stdin);
			cin.ignore();
		}
		void display() //showing data members
		{
			cout<<"\nYour brand bag name is **"<<brand<<"** and the dimensions are: "
			<<length<<"L "<<width<<"W "<<height<<"H "<<endl;
		}
		Bags (const Bags &bi) //copy constructor
		{
			brand = bi.brand;
			length = bi.length;
			width = bi.width;
			height = bi.height;
			cout<<"\nDo you have the same bag??"<<endl;
		}
		Bags() //default constructor
		{
			brand = "Adidas";
			length = 35;
			width = 20;
			height = 45;
		}
		//declare as friend function using prototype
		friend void check(Bags,Bags,Bags);
	
};
//function to check value similarity and display
void check(Bags a, Bags b, Bags c)
{	//check for heigh similarity among 3 objects
	if(a.height==b.height && a.height==c.height)
		cout<<"\nCommon height for all 3 bags"<<endl;
	else
		cout<<"\n--not all bags have the same heights--"<<endl;
	cout<<"--------------------------------";
}

int main()
{ //need to developed by adding object K, L and M;
	Bags K[3]; //declare array of 3 objects
	for(int i=0;i<3;i++) //loop to set data for each object
		K[i].setdata();
	check(K[0],K[1],K[2]); //call friend function by passing objects
	
	
}
