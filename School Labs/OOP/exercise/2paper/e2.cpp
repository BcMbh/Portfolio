#include<iostream>
using namespace std;
class Product
{ 
    string id, year;
 
    public:
    void setProduct(string pid, string y)
    { id = pid;
      year = y;
    }

    friend class Defect;
}; 

class Defect
{  string day[5];
   int qty[5];
   Product JC;
    
  public:
	  void setdata(string d[], int no[])
	  {  string pid, y;
	     cout<<"Enter the product id        :";
	     getline(cin, pid);
	     cout<<"Enter the manufactured year :";
	     getline(cin, y);

	    JC.setProduct(pid,y);

        for (int i = 0; i < 5; ++i) {
            day[i] = d[i];
            qty[i] = no[i];
        }
	     
	  }

	  void findminmax()
	  { 
	    string minday, maxday;
	    int min, max;
        min = max = qty[0];
        minday = maxday = day[0];
	    
	    for(int i = 0; i < 5; ++i) {
            if (qty[i] < min) {
                min = qty[i];
                minday = day[i];
            }
            if (qty[i] > max) {
                max = qty[i];
                maxday = day[i];
            }
        }

	    cout<<"\n\nDefect report"<<endl;
	    cout<<"--------------"<<endl;
	    cout<<"Product id :"<<JC.id<<", year manufactured" 
          ":"<<JC.year<<endl;
	    cout<<"Min defect :"<< min <<" Day :"<< minday <<endl;
	    cout<<"Max defect :"<< max <<" Day :"<< maxday <<endl;;
		
	  }
};

int main()
{  
   int i, no[5] = { 3, 7, 0, 5, 2};
   string day[5] = { "Mon", "Tues", "Wed", "Thurs", "Fri"};
   Defect D1;
   D1.setdata(day, no);
   D1.findminmax();
   return 0;
}
