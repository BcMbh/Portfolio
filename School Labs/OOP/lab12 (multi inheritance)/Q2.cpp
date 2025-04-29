/*
Lab 12
Question 2
Multiple inheritance and parent accessor function
*/
 
#include<iostream>
#include<iomanip>
using namespace std;
//define parent class
class Staff
{
	protected: //protected data members
		string name, id;
		int age;
		float salary, nett_salary;			
	public: //public member functions
		void setdata()
		{	//prompt user for input except nett_salary
			fflush(stdin); //clear buffer
			cout<<"\nEnter Name"<<setw(7)<<": ";
			getline(cin,name);
			cout<<"Enter ID"<<setw(9)<<": ";
			getline(cin,id);
			cout<<"Enter Age"<<setw(8)<<": ";
			cin>>age;
			cout<<"Enter Salary"<<setw(8)<<": RM ";
			cin>>salary;
		}
		float getNettSalary()
		{	//accessor function
			return nett_salary;
		}
};
//define child class inheriting parent class publicly
class Executive:public Staff
{
	private: //private data members
		int OT_hrs;
		float rate;
	public: //public member functions
		void setExecutive()
		{	//mutator functions
			cout<<"Enter OT Hours : ";
			cin>>OT_hrs;
			cout<<"Enter Rate"<<setw(10)<<": RM ";
			cin>>rate;
		}
		void cal_salary_exec()
		{	//function to calculate executive salary
			nett_salary = salary + (OT_hrs * rate);
		}
		void display()
		{	//display executive staff details
			cout<<fixed<<setprecision(2);
			cout<<"\nName"<<setw(10)<<": "<<name<<endl;
			cout<<"ID"<<setw(12)<<": "<<id<<endl;
			cout<<"Age"<<setw(11)<<": "<<age<<endl;
			cout<<"Salary"<<setw(11)<<": RM "<<salary<<endl;
			cout<<"OT Hours"<<setw(6)<<": "<<OT_hrs<<endl;
			cout<<"OT Rate"<<setw(10)<<": RM "<<rate<<endl;
			cout<<"Nett Salary : RM "<<nett_salary<<endl;
		}
};
//define child class inheriting parent class publicly
class Salesperson:public Staff
{
	private: //private data members
		int units;
		float bonus;
	public: //public member functions
		void setSalesperson()
		{	//mutator function
			cout<<"Enter Units"<<setw(6)<<": ";
			cin>>units;
		}	
		void cal_salary_sales()
		{	//function to calculate salesperson salary
			//condition to set bonus to salary
			if(units>500.00)
				bonus = 500.00;
			else
				bonus = 250.00;
			//calculate nett salary
			nett_salary = salary + bonus;
		}
		void display()
		{	//display salesperson staff salary
			fflush(stdin);
			cout<<fixed<<setprecision(2);
			cout<<"\nName"<<setw(10)<<": "<<name<<endl;
			cout<<"ID"<<setw(12)<<": "<<id<<endl;
			cout<<"Age"<<setw(11)<<": "<<age<<endl;
			cout<<"Salary"<<setw(11)<<": RM "<<salary<<endl;
			cout<<"Units"<<setw(9)<<": "<<units<<endl;
			cout<<"Bonus"<<setw(12)<<": RM "<<bonus<<endl;
			cout<<"Nett Salary : RM "<<nett_salary<<endl;
		}
};
 
int main()
{
	char cont;
	//initialize variables to accumulate total staff and payouts
	int select,count = 0;
	float nett, total = 0.00;
	//prompt user for decision
	cout<<"Do you want to continue? ";
	cin>>cont;
	while(cont == 'Y' || cont == 'y')
	{	//prompt user to select type of staff
		cout<<"Enter [1] for Executive OR [2] for Salesperson: ";
		cin>>select;
		switch(select)
		{
			case 1:
				{	//declare class object
					Executive e;
					//call object methods
					e.setdata();
					e.setExecutive();
					e.cal_salary_exec();
					e.display();
					//access calculated nett salary
					nett = e.getNettSalary();
					break;
				}
			case 2:
				{	//declare class object
					Salesperson s;
					//call object methods
					s.setdata();
					s.setSalesperson();
					s.cal_salary_sales();
					s.display();
					//access calculate nett salary
					nett = s.getNettSalary();
					break;
				}
			otherwise:
				cout<<"Invalid.";
		}
		//increment for number of staff and payout
		count++;
		total += nett;
		//prompt for decision		
		cout<<"\nDo you want to continue? ";
		cin>>cont;
	}
	//display total staff and payout
	cout<<"\nTotal Staff: "<<count<<endl;
	cout<<"Total Payouts is RM "<<total<<endl;
}