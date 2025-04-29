#include <iostream>
#include <iomanip>
using namespace std;
class HQ
{
	protected:	
	int a,b,m,n;
	public: 
		HQ(){	
			a=10,b=13;	 
		}

		void set_data(int x, int y)	{	
			a=x, b=y;	
		}

		HQ(int x, int y) { 
			a=x, b=y;	
		}

		void calculate() {
			m=(a * b );	
			n = m++; 
		}

		void display()
		{
			cout<<"HQ m : "<<m<<endl;
			cout<<"HQ n : "<<n<<endl;
			cout<<"HQ a : "<<a<<endl;
			cout<<"HQ b : "<<b<<endl;
		}
};
class SUB:public HQ
{
	private: int a,b;
	public:
		SUB(int x,int y):HQ(x,y) {	
			a=x;b=y; 
		}

		void display()	{	
			HQ::display();	
		}
};
int main()
{
	HQ h;
	int x=3,y=4;
	h.set_data(x,y);
	h.calculate();
	h.display();
	SUB s(5,6);
	s.calculate();
	s.display();
	
}
