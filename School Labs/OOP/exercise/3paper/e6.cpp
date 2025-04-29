#include<iostream>                                         
using namespace std;  

class Job
{    protected:
 	  float salary;	

     public:
	   virtual void display ( float s ) 
	   {  salary = s;
            cout<< "= Your salary is :: RM " << salary<< endl;
	   }
	   
	   virtual ~Job()
	   { cout<< "Job class" << endl << endl; }
};

class Lecturer: public Job
{      void display( float s )
	 {  salary = s;
          cout<< "This is a Lecturer’s salary :" << salary << endl;
	 }
        
       ~Lecturer()
	{  static int num=1;
	   cout << "Lecturer " << num << " salary calculation done" <<   
         endl ;
	   num++;
	  	
	 }
	
};
int main()
{   Job j; 
    Job *p = new Lecturer;
    p->display(1500);
    delete p;
    p = new Lecturer;
    p->display(2590);
    delete p;
    p = &j;
    p->display(150);   
   return 0;
}
