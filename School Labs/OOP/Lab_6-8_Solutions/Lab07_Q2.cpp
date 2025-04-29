/*
Lab 07
Question 2
Friend function access private data members
*/

#include<iostream>
#include<iomanip>
using namespace std;
//define class
class ICE_CREAM
{
	private: //private data members
		string flavour;
		int number;
		float price;
	public: //public member functions
		void menu(); //member function
		void setflavour(); //mutator function
		void setHowMany(); //mutator function
		friend void display_receipt(ICE_CREAM); //friend function
		ICE_CREAM(); //default constructor
};

void ICE_CREAM::menu() //display menu information
{
	cout<<"\n==========================================="<<endl;
	cout<<"=== CHOOSE FLAVOUR ==="<<endl;
	cout<<"==========================================="<<endl;
	cout<<"[1] === Strawberry Flavour RM 3.50"<<endl;
	cout<<"[2] === Chocolate Flavour RM 2.50"<<endl;
	cout<<"[3] === Vanilla Flavour RM 1.50"<<endl;
	cout<<"[4] === Durian Flavour RM 0.50"<<endl;
}

void ICE_CREAM::setflavour()
{	//get user input
	int choice;
	cout<<"\nChoice of flavour: ";
	cin>>choice;
	//switch statement to set flavour and price
	switch(choice)
	{
		case 1: flavour = "Strawberry"; price = 3.50; break;
		case 2: flavour = "Chocolate"; price = 2.50; break;
		case 3: flavour = "Vanilla"; price = 1.50; break;
		case 4: flavour = "Durian"; price = 0.50; break;
	}
}

void ICE_CREAM::setHowMany()
{	//get user input to set amount
	cout<<"How many: ";
	cin>>number;
}

ICE_CREAM::ICE_CREAM() 
{	//default constructor to display title
	cout<<"BARNEY'S HOUSE OF ICE"<<endl;
}

void display_receipt(ICE_CREAM IC) //friend function accepting object
{	//display payment details by accessing class object
	cout<<"\n==========================================="<<endl;
	cout<<"=== PAYMENT ==="<<endl;
	cout<<"==========================================="<<endl;
	cout<<"Flavour\t\t: "<<IC.flavour<<endl;
	cout<<"Total Price\t: RM "<<fixed<<setprecision(2)
	<<IC.price*IC.number<<endl;
}

int main()
{	
	ICE_CREAM IC; //declare class object
	IC.menu(); //call member function to show menu
	IC.setflavour(); //call member function to select flavour
	IC.setHowMany();//call member function to set amount
	display_receipt(IC); //call friend function to print receipt
}
