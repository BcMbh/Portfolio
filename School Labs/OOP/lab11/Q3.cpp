/*
Lab 11
Question 3
Protected class inheritance and dynamic array of objects
*/
 
#include<iostream>
using namespace std;
//define class
class Product
{
	private: //private data member
		int prodID;
	protected: //protcted data member
		float total_price;
	public: //public member functions
		Product() //default constructor
		{
			total_price = 0.0;
		}
		int getProd_ID() //accessor function
		{
			return prodID;
		}
		void input_ProdID() //mutator function
		{
			cout<<"\nEnter product ID : ";
			cin>>prodID;
		}
};
//define class that protectively inherits another class
class CanFood:protected Product
{
	private: //private data members
		float unit_price;
		int order_unit;
	public: //public member functions
		void get_Product()
		{	//mutator function
			input_ProdID(); //call parent function to set data
			//prompt user to enter details
			cout<<"Enter price\t : RM";
			cin>>unit_price;
			cout<<"Enter order unit : ";
			cin>>order_unit;
		}
		void calculate_Total()
		{	//function to calculate total price
			total_price = unit_price*order_unit;
		}
		void display_product()
		{	//function to display details using parent accessor function
			cout<<"\nProduct ID\t: "<<getProd_ID()<<endl;
			cout<<"Total price\t: RM"<<total_price<<endl;
		}
};
 
int main()
{
	int in;
	//prompt user for number of types
	cout<<"How many types of canned food? ";
	cin>>in;
	CanFood *tp;//declare pointer variable
	//declare dynamic array of objects using pointer 
	tp = new CanFood[in];
	//loop through array of objects to set and calculate data
	for(int i=0;i<in;i++)
	{	//call object methods
		(tp+i)->get_Product();
		(tp+i)->calculate_Total();
		//alternative ways to call object methods
//		(*(tp+i)).get_Product();
//		(*(tp+i)).calculate_Total();
//		tp[i].get_Product();
//		tp[i].calculate_Total();
	}
	//loop to display details of object
	for(int i=0;i<in;i++)
	{
		(tp+i)->display_product();
//		(*(tp+i)).display_product();
//		tp[i].display_product();
	}
	//delete dynamic array of objects
	delete [] tp;	
}