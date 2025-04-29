/*
Lab 01
Question 2(b)
Increment, for loop, and modulo operator
*/
 
#include<iostream>
 
using namespace std;
 
int main()
{
	//declare variables to store counts
	int number, evencount = 0, oddcount = 0, total = 0;
	//for loop to repeatedly get user inputs and check even/odd
	for(int i = 0; i<10; i++) //set condition to loop 10 times with increment
	{
		//prompt user to enter 10 numbers
		cout<<"Enter a number :";
		cin>>number;
		//if-else selection structure to check even/odd
		if(number%2 == 0) //modulo operature to check if remainder =0 after division by 2
			evencount++;
		else
			oddcount++;
		//accumulate value of every number entered to get total
		total += number;
	} 
	//display number of even/odd and total of all numbers
	cout<<"\nThere are "<<evencount<<" even numbers and "<<oddcount<<" odd numbers.\n";
	cout<<"The total of all the 10 numbers are "<<total;
}