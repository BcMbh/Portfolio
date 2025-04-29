/*
Lab 01
Question 2(c)
Do-while loop and stopping condition
*/
 
#include<iostream>
 
using namespace std;
 
int main()
{
	//declare variables for condition checking, store input, and accumulate total	
	int number, total = 0;
	//do-while loop to repeat
	do
	{
		//prompt user input for number
		cout<<"Enter a number :";
		cin>>number;
		//check if input value is exit condition
		if(number != 99)
			total = number; //trigger loop termination
//		else
			total += number; //accumulate inputs
	} while(number != 99); //stopping condition
	//display total input
	cout<<"The total is "<<total;
}