#include<iostream>
using namespace std;

class Receipt
{     float total;	
     public:
        Receipt(float t)
        { total = t;
        }

        Receipt operator+(Receipt R)
        {
            return Receipt(total + R.total);
        }
     
	   void print()
	   { cout<<total<<endl;
	   }
   
};

int main()
{  Receipt a1(500.00) , a2(120.55);
   Receipt a3 = a1.operator+(a2); 
   cout<<"Combined total is ";
   a3.print();
   return 0;
}

