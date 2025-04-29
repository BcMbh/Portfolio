#include <iostream>
using namespace std;

class Table
 {  private: int width_measure, length_measure; 
    public:
      Table(){
        cout<<"~~Object Created~~"<<endl;
      }
      
	      void Set_Measurement (int L, int T)
      {   width_measure = L;  
          length_measure = T;        
      }
      
       
       friend void findLargest(Table[]);
 } ;

void findLargest(Table t[]) {
    int largestArea = 0;
    int largestIndex = 0;

    for (int i = 0; i < 5; ++i) {
        int area = t[i].width_measure * t[i].length_measure;
        cout << "Table " << i + 1 << " area: " << area << endl;
        if (area > largestArea) {
            largestArea = area;
            largestIndex = i;
        }
    }

    cout << "The largest table area is Table " << largestIndex + 1 << " with area: " << largestArea << endl;
}
int main()
 {
     Table t[5];
     int i  = 0, x, y;
     while( i < 5 )
     { cout<<"Enter the 5 tables' width and length :\n";
       cin>>x>>y;
	      t[i]. Set_Measurement(x,y);
       i++;
     }
     
     findLargest(t);
     return 0;
 }
