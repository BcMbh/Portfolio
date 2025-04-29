/*
Lab 07
Question 3
Friend function call by reference using pointer
*/

#include<iostream>
using namespace std;
//define class
class NumberGame
{ 	int array[5]; //private data member
	public: //public member functions
		//----------- (a)-----------
		NumberGame() //default constructor to initialize array
		{
			array[0]=15;
			array[1]=20;
			array[2]=33;
			array[3]=38;
			array[4]=100;
			//int array[5]={15,20,33,38,100};
		}
		//declare friend function with prototype
		friend void search(NumberGame , int*);
};
//----------- (b)-----------
//function to find number in array
void search(NumberGame NG, int* num)
{ 	//two input parameters with call by reference pointer
	int i = 0, end = 0;
	//loop to go through array elements for search
	do
	{	
		if(NG.array[i]==*num) //condition to find number
		{
			end = 1;
		}
		i++; //increment to index array
		if(i==5) //number not found at the end of search
		{
			end=1;	
		}
	} while(end!=1); //stop search if found/not found flag triggered
	
	// statements to display output message based on flag
	if(i==5)
		cout<<*num<<" is NOT found!"<<endl;
	else
		cout<<*num<<" is found!"<<endl;
}

int main()
{ 	NumberGame G ; //declare object
	int num;
	//prompt user number to be searched
	cout<<"Enter a number :";
	cin>>num;
	search(G, &num); //call function using address
	return 0;
}
