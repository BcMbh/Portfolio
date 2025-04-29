/*
Lab 06
Question 3
Constructor, destructor, mutator for array of objects
*/

#include<iostream>
#include<iomanip>
using namespace std;
//define class
class Books
{
	private: //private data members
		string isbnNo, title, author;
		float price, discountedprice, discountperc;
	public: //public member functions
		Books(); //default constructor
		Books(string,string,string,float,float); //parameterized constructor
		void set_Data(); //mutator function
		void calcDiscountedPrice(); //for calculation
		void print(); //for display
		float getDiscountedPrice(); //accessor function
		~Books(); //desctructor
};

void Books::set_Data() //mutator function
{	//get user inputs and set to appropriate variables
	fflush(stdin); //clear buffer
	cout<<"\nEnter ISBN\t\t: ";
	getline(cin,isbnNo);
	cout<<"Enter Title\t\t: ";
	getline(cin,title);
	cout<<"Enter Author's name\t: ";
	getline(cin,author);
	cout<<"Enter price\t\t: RM ";
	cin>>price;
	cout<<"Enter discount (%)\t: ";
	cin>>discountperc;
}

void Books::calcDiscountedPrice() //void has no return
{	//calculate price after minus discounted amount
	discountedprice = price*(100-discountperc)/100;
}

void Books::print()
{	//display book details
	cout<<"\n--------------------------------------------------------"<<endl;
	cout<<"\t\tBook Details"<<endl;
	cout<<"--------------------------------------------------------"<<endl;
	cout<<"ISBN\t\t: "<<isbnNo<<endl;
	cout<<"Title\t\t: "<<title<<endl;
	cout<<"Author\t\t: "<<author<<endl;
	cout<<"Original Price\t: RM "<<fixed<<setprecision(2)<<price<<endl;
	cout<<"Discounted Price: RM "<<discountedprice<<endl;
}

float Books::getDiscountedPrice(){return discountedprice;} //accessor function

Books::Books() //default constructor
{
	isbnNo =""; title=""; author="";
	price=0.00; discountperc=0;
}

Books::Books(string n, string t, string a, float p, float d)
{	//parameterized constructor
	isbnNo = n; title = t; author = a;
	price = p; discountperc = d; 
}

Books::~Books(){cout<<"\nEnjoy reading "<<title<<endl;} //destructor

//function accept object by refreence using a reference object as argument
void func(Books &B)
{	//call object functions
	B.set_Data();
	B.calcDiscountedPrice();
	B.print();
}

int main()
{	//initialize object with data values
	Books B1("102009912","7 Habits of Highly Effective People",
			 "Stephen Covey",400.00,30);
	//call functions of object to calculate and display data	
	cout<<".........Book of the Month......"<<endl;	
	B1.calcDiscountedPrice();
	B1.print();
	//declare array of objects
	Books B2[3];
	float expensive = 0.00, discprc;
	int below = 0;
	
	cout<<"\nNow we shall enter and display data for 3 special books...."<<endl;
	//loop to call functions for array of objects
	for(int i=0;i<3;i++)
	{
		func(B2[i]); //function calls object mutator, calculate discount, display
		discprc = B2[i].getDiscountedPrice(); //access price aftre discount
		//determine most expensive book
		if(expensive<discprc)
		{
			expensive = discprc;
		}
		//accumulate count of books with price below 30 after discount
		if(discprc<30)
			below++;		
	}
	//display most expensive book price and number of books below 30 after discount
	cout<<"\n--------------------------------------------------------"<<endl;
	cout<<"The most expensive book is RM "<<expensive<<endl;
	cout<<"The number of books that are below RM 30 are :"<<below<<endl;
	return 0;
}
