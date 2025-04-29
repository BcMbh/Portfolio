#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
const double PI = 3.14,
ICEPACK_SIZE = 3;   // in litre

class IceCream
{  	double ps, packSizeRad, IcePack, bowlPerPack;
  public:
           void input()
           {  cout<<"\nEnter the Ice-Cream Pack size (in Litre): ";
              cin>>ps;
           }

            void calculate()
     		{  packSizeRad = ps / 2;
	              IcePack = PI * pow(packSizeRad, 2);
	              bowlPerPack = IcePack / ICEPACK_SIZE;
	 	 	}

	 		double getServeBowlPerIce()
	 		{ return bowlPerPack; 	 }
};

int main()
{	
    IceCream *ice;
    ice = new IceCream[3];

	    for(int i=0; i<3; i++)
	    {
                 ice->input();
                 ice->calculate();
                 cout<<"This Ice-Cream pack can be served up to "<<ice->getServeBowlPerIce()<<"Special bowls"<<endl;
        }

      return 0;
}
