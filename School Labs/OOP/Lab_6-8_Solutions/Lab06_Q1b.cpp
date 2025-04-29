/*
Lab 06
Question 1(b)
Constructor and destructor with array of objects
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
{ 	//initialize array of 4 objects with hardcoded data
	MasterStudent MS[4] = {MasterStudent("Philip Morales", "Working with Generation X employees: food industry", 1),
						MasterStudent("Cameron Connor","Collective Co-Creation within the Open Source Software Community", 1),
						MasterStudent("Meriam Miles","What Makes Online Video Advertisements Go Viral?",0),
						MasterStudent("Dory Dean","Social media use for corporate communications",0)};
	//loop to access data members of each object in array and display details
	for(int i=0;i<4;i++)
	{
	cout<<"\n================================="<<endl;
	cout<<" Masters Student Details "<<i+1<<endl;
	cout<<"================================="<<endl;
	cout<<"Name \t: "<<MS[i].getName()<<endl;
	cout<<"Title \t: "<<MS[i].getTitle()<<endl;
	cout<<"Status \t: ";
	if(MS[i].getStatus() ==1) cout<<"Approved"<<endl;
	else cout<<"Pending"<<endl;
	}
}
