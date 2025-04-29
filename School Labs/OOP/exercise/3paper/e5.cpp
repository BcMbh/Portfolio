#include<iostream>                                         // line 1
using namespace std;                                       // line 2
                                                           // line 3
class Coordinate                                           // line 4
{                                                          // line 5
 private:                                                  // line 6
		double a,b;                                    // line 7
 public:                                                   // line 8
	Coordinate  () { a = b = 0.0; }                      // line 9
                                                          // line 10
	Coordinate (double a_arg, double b_arg)            // line 11
       {    
            a = a_arg;                               // line 12
		    b = b_arg;                               // line 13 
       }                                                  // line 14
                                                          // line 15    
    Coordinate operator+(const Coordinate  p) {                      // line 16
	    return Coordinate(a + p.a, b + p.b);                // line 17
    }                                                       // line 18
                                                          // line 19
       void display()                                     // line 20
        {   cout<<"a :"<<a<<", b :"<<b<<endl; }           // line 21
};                                                        // line 22
                                                          // line 23
int main()                                                // line 24
{  Coordinate ob1, ob2(1.5, 3.5), ob3 (5.0, 7.0) ;        // line 25
   ob1 = ob2 + ob3;                                       // line 26
   ob1.display();                                         // line 27
   ob2.display();                                         // line 28
   return 0;                                              // line 29
}                                                         // line 30
