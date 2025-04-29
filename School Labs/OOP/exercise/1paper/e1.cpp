#include<iostream>
#include<iomanip>
using namespace std;
class beverage
{
   private:
		string name;
        float price;

	public:
		void set_data(string n, float p){
            name=n;
            price=p;
        }

        void display(){
            cout<<name<<"   "<<price<<endl;
        }
	 
};
int main()
{
	string n;	
    float p;	
    beverage b[3];

	for(int i=0;i<3;i++)
	{
		cout<<"Enter beverage name : ";
		cin>>n;
		cout<<"Enter beverage price : ";
		cin>>p;
		b[i].set_data(n,p);
	}

	for(int i=0;i<3;i++)
	{
		b[i].display();
	}
}
