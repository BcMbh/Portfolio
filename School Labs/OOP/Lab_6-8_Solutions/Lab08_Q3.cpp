/*
Lab 08
Question 3
Calling friend class methods
*/
#include<iostream>
#include <limits>
using namespace std;
//define class
class Ticket
{
	private: //private data members
		int no; float price;
		//friend class Student; //declare friend class
	public: //public member functions
		Ticket() //default constructor
		{ price = 10.00; }
		void setTickets()
		{	//prompt user input for number of tickets
			cout<<"Please enter number of tickets to purchase: ";
			cin>>no;
		}
};
//define class
class Student
{
	private: //private data members
		string id, name, purchase;
		Ticket p;
	public: //public member functions
		void setStudent()
		{	
			fflush(stdin); //clear buffer for input with [space]
			//promp user input for name and id
			cout<<"\nEnter ID: ";
			getline(cin,id);
			cout<<"Enter Name: ";
			getline(cin,name);
		}
		void ticket_entry()
		{	//prompt user input for purchase decision
			char sel;
			cout<<"Do you want to purchase charity tickets? ";
			cout<<"[Enter Y or N]: ";
			cin>>sel;
			//if-else statement to call function or displya message
			if(sel=='Y')
			{	//set purchase and call function of friend class
				purchase = "Yes";
				p.setTickets();
			}
			else
				cout<<"--------No ticket purchased--------"<<endl;
			
			cin.clear();cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		void display()
		{	//display student and additional details
			cout<<"\n--------------------------------"<<endl;
			cout<<"	STUDENT DETAILS"<<endl;
			cout<<"--------------------------------"<<endl;
			cout<<"ID	:"<<id<<endl;
			cout<<"Name	:"<<name<<endl;
			cout<<"\n--------------------------------"<<endl;
			cout<<"	ADDITIONAL DETAILS"<<endl;
			cout<<"--------------------------------"<<endl;
			//if-else statement to check purchase details
			if(purchase=="Yes")
			{
				cout<<"You've purchased "<<p.no<<" Tickets"<<endl;
				cout<<"Total amoun: RM "<<p.no*p.price<<endl;
			}
			else
			{
				cout<<"You've not purchased any tickets"<<endl;
			}
		}
};

int main()
{
	Student s[3]; //declare array of 3 objects
	//loop to call functins of every array object
	for(int i = 0;i<3;i++)
	{
		s[i].setStudent();
		s[i].ticket_entry();
		s[i].display();
	}
}
