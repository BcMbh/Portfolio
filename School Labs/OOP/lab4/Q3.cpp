#include<iostream>
#include<string.h>
using namespace std;
 
//define class
class Achievement
{	//private data members
	string class_name;
	int score;
	//public member functions
	public:
		//set all data members to the appropriate variables
		void set_data(string n, int s) 
		{
			class_name = n;
			score = s;
		}
		//display achievement following given scale
		void display_scale()
		{
			cout<<"===================================="<<endl;
			cout<<"\t"<<class_name<<endl;
			cout<<"The Class Passing Grade Achievement:"<<score<<"%"<<endl;
			//selection structure to determine stars
			if(score<=100 && score>=85)
				cout<<"*****"<<endl;
			else if(score<85 && score>=70)
				cout<<"****"<<endl;
			else if(score<70 && score>=60)
				cout<<"***"<<endl;
			else if(score<60 && score >=50)
				cout<<"**"<<endl;
			else
				cout<<"Poor achievement";
		}
};
 
int main()
{	//declare variables and array of class objects
	int num = 4;
	string cl;
	int ac;
	Achievement A[num];
	cout<<"--------------------------------------------------------------"<<endl;
	cout<<"\tEnter Class Achievement"<<endl;
	cout<<"--------------------------------------------------------------"<<endl;
	//loop to set data of 4 Standard 6 classes into array of objects
	for(int i=0;i<num;i++)
	{
		cout<<"\nEnter the class name\t\t:";
		cin>>cl;
		cout<<"The class achievement (%)\t:";
		cin>>ac;
		A[i].set_data(cl,ac);
	}
	//loop to display the summary results for 4 classes
	cout<<"\n THE SUMMARY OF UPSR TRIAL EXAM RESULT"<<endl;
	for(int i=0;i<num;i++)
	{
		A[i].display_scale();
	}
	cout<<"\n===================================="<<endl;
}