#include<iostream>
using namespace std;
int main()
{	//declare variables
	int subject, num;
	float total_payment, average_payment;
	float *fees; //pointer variable
	//prompt user for number of subjects
	cout<<"How many subjects have you registered: ";
	cin>>subject;
	//declare dynamic array using number of subjects
	fees = new float[subject];
	total_payment = 0; //initialize value for increment
	//loop to go through all subjects
	for(num=0;num<subject;num++)
	{	//prompt use to input fees for subject
		cout<<"Class "<<num+1<<" fees charge: RM ";
		cin>>fees[num];
		//accumulate total payment to be made
		total_payment += fees[num];
	}
	//display payment details entered by user
	cout<<"\n===== PAYMENT DETAILS ====="<<endl;
	cout<<"fees charges you have entered: ";
	for(num=0;num<subject;num++)
	{
		cout<<fees[num]<<"(RM)... ";
	}
	//calculate average payment
	average_payment = total_payment/subject;
	//display total and minimmum payment to be made
	cout<<"\nTotal payment to be made: RM "<<total_payment<<endl;
	cout<<"Minimum payment (Average of total payment): RM "<<average_payment<<endl;
	return 0;
}