#include<iostream>
#include<iomanip>
 
using namespace std;
 
//given class
class TravelPackage
{
	public:
		char package;
		int noAdult, noChild;
		float adultPrice, childPrice, discount, totalPrice;
};
 
int main()
{
	//initialize class object
	TravelPackage Tp;
 
	//do-while loop to promp user for correct package selection
	do
	{
		cout<<"\nSelect travel package <A,B,C>:";
		cin>>Tp.package; //store selection in object
		//message to indicate incorrect input
		if(Tp.package!='A'&& Tp.package !='B' && Tp.package && 'C')
			cout<<"Invalid selection.\n";
	}while(Tp.package!='A'&& Tp.package !='B' && Tp.package && 'C');
	//switch statement to determin price based on available package
	switch (Tp.package)
	{
		case 'A': 
			Tp.adultPrice = 1000.00; 
			Tp.childPrice = 500.00;
			break;
		case 'B':
			Tp.adultPrice = 800.00;
			Tp.childPrice = 600.00;
			break;
		case 'C':
			Tp.adultPrice = 500.00;
			Tp.childPrice = 300.00;
			break;
	}

	//store number of people into object
	cout<<"\nEnter no of adult :";
	cin>>Tp.noAdult;
	cout<<"Enter no of children :";
	cin>>Tp.noChild;

	//calculate total price based on selected package and number of adults and children input
	Tp.totalPrice = Tp.adultPrice * Tp.noAdult + Tp.childPrice * Tp.noChild;
	
    //if statement to deduct 20% if price greater than RM3k
	if(Tp.totalPrice>3000.00)
		Tp.totalPrice *= 0.8;
	
    //display total price
	cout<<"\nTotal price : RM"<<fixed<<setprecision(2)<<Tp.totalPrice;
}