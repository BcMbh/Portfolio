/*
Lab 06
Question 1(a)
Default constructor, parameterized constructor, destructor
*/

#include<iostream>
using namespace std;
//define class
class MasterStudent
{ 	//private data members
	string name, title;
	int status;
	public: //public member functions
	//parameterized constructor
	MasterStudent(string n, string t, int x)
	{ 	name = n;
		title = t;
		status = x;
	}
	//default constructor
	MasterStudent()
	{ 	name = "Peter";
		title = "A Study on the Usability Factors of Mobile Apps.";
		status = 1;
	}
	//accessor functions
	int getStatus()
	{ 	return status;
	}
	string getName()
	{ 	return name;
	}
	string getTitle()
	{ 	return title;
	}
	//destructor
	~MasterStudent()
	{ 	cout<<"\n\n~End of Details~Student~"<<name<<endl;
	}
};

int main()
{ 	MasterStudent MS1; //initialize class object using default constructor
	cout<<"================================="<<endl;
	cout<<" Masters Student Details "<<endl;
	cout<<"================================="<<endl;
	//access and show private data members
	cout<<"Name \t: "<<MS1.getName()<<endl;
	cout<<"Title \t: "<<MS1.getTitle()<<endl;
	cout<<"Status \t: ";
	//check and print status
	if(MS1.getStatus() ==1) cout<<"Approved"<<endl;
	else cout<<"Pending"<<endl;
//Create another object passing the values
//"Aliana Mahmud" for name, "Customer Satisfaction towards Green Products" for title, 0 for status
//Use the cout statements given earlier to display the content of the new object.
//refer to label X for the output to be displayed
	MasterStudent MS2("Aliana Mahmud","Customer Statisfaction towards Green Products",0);
	cout<<"================================="<<endl;
	cout<<" Masters Student Details "<<endl;
	cout<<"================================="<<endl;
	cout<<"Name \t: "<<MS2.getName()<<endl;
	cout<<"Title \t: "<<MS2.getTitle()<<endl;
	cout<<"Status \t: ";
	if(MS2.getStatus() ==1) cout<<"Approved"<<endl;
	else cout<<"Pending"<<endl;
}
