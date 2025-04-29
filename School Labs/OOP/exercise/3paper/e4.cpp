#include <iostream>
#include <cmath>
using namespace std;

class Triangle
{  protected:
		  double a, b, c;
   public: 
	      Triangle(double x=3)
	      {  a=x; b=3; c=3;
	         cout<<"--PP1--"<<endl;
	      }
	      Triangle(double x, double y)
	      {  a=x; b=y;
	         cout<<"--PC2--"<<endl;
	      }
	      
};

class Pythagoras : protected Triangle
{
    public:
    	
    	 Pythagoras(double x, double y) : Triangle(x,y)
    	 { cout<<"--Pythagoras--"<<endl;
    	 }
	  	  double find();	 	  
};

double Pythagoras::find()
{ 
		c = sqrt(a*a + b*b); 
		return c; 
}
	
int main()
{
 	  int n, i;
 	  double side1 = 3, side2 = 4;
 	
 	  Pythagoras *may = new Pythagoras(side1, side2);
      cout << "Hypotenuse: " << may->find() << endl;
      
      delete may;
 
}
