/*
Lab 06
Question 2
Overloaded constructors and mutator functions
*/

#include<iostream>
using namespace std;
//define class
class Employee
{	//private data members
	string name, department, position;
	int idNumber;
	public://public member functions
		//parameterized constructor (4 parameters)
		Employee(string n,int id, string dept, string post)
		{
			name = n;
			idNumber = id;
			department = dept;
			position = post;
		}
		//parameterized constructor (2 parameters)
		Employee(string n, int id)
		{
			name = n;
			idNumber = id;
			department = "";
			position = "";
		}
		//default constructor
		Employee()
		{
			name = "";
			idNumber = 0;
			department = "";
			position = "";
		}
		//mutator functions
		void setName(string n){ name = n; }
		void setID(int id){ idNumber = id; }
		void setDept(string dept){ department = dept; }
		void setPost(string post){ position = post; }
		//accessor functions
		string getName(){return name;}
		int getID(){return idNumber;}
		string getDept(){return department;}
		string getPost(){return position;}
};

void displayData(Employee); //additional function to display data

int main()
{	//initialize object with parameterized constructor
	Employee SM("Susan Meyers",47899,"Accounting","Vice President");
	//initialize object with parameterized constructor and setting data with mutator functions
	Employee MJ("Mark Jones",39119);
	MJ.setDept("IT");
	MJ.setPost("Programmer");
	//initialize object with default constructor and setting data with mutator functions
	Employee JR;
	JR.setName("Joy Rogers");
	JR.setID(81774);
	JR.setDept("Manufacturing");
	JR.setPost("Engineer");
	//display data in objects
	displayData(SM);
	displayData(MJ);
	displayData(JR);
}
//display data function
void displayData(Employee E)
{	//access and display private data of object
	cout<<"\nName: "<<E.getName()<<endl;
	cout<<"ID Number: "<<E.getID()<<endl;
	cout<<"Department: "<<E.getDept()<<endl;
	cout<<"Position: "<<E.getPost()<<endl;
}
