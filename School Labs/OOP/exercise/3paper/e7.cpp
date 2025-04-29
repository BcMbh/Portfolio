#include<iostream>
using namespace std;

class CarProduct
{  string mo;
   int qty;

  public:
    CarProduct()  //constructor
    { cout<<"----Generating----"<<endl;  }

    ~CarProduct()
    { cout<<"----The end----"<<endl;
    }

     void setdata(string m, int q) //mutator
     {  mo = m;
	  qty = q;
     }
	
	  string get_mo()
	  { return mo;}
	
        int get_qty()
	  { return qty;}
	 
};

int main()
{   string mo[5]= { "Jan", "Feb", "Mac", "Apr", "Mei"};
    int i, q[5] = { 43, 65, 4, 0, 14};
   
    CarProduct* M1 = new CarProduct[5];
	
     for( i=0; i<5; i++)
     {  M1[i].setdata(mo[i], q[i]);}  
	
      i=0;
	while(i<5)
	{   
        int no = M1[i].get_qty(), high=no/10,low=no%10;
        
        cout<<"Month "<< M1[i].get_mo()<<": ";

        for(int j = 0; j < high; j++){
            cout<<"* ";
        }
        for(int j = 0; j < low; j++){
            cout<<"# ";
        }
        if(!no){
            cout<<"No production";
        }

        cout<<endl;
        i++;
	}

    delete[] M1;
    return 0;
}
