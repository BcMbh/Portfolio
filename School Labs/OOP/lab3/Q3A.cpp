#include<iostream>
using namespace std;
 
//class declaration
class Cuboid
{ 
  int length, width, height, volume;//private data member by default
  public:
    //prompt user for input
    void setdata()
    {
      cout<<"Enter the width, length, height of a Cuboid object:";
      cin>>width>>length>>height;
    }
    void findVolume();//calculate the cube volume
    void display()
    {
      cout<<"\n-------------Display Cuboid Data--------------"<<endl;
      cout<<"Width"<<width<<"cm"<<endl;
      cout<<"Length"<<length<<"cm"<<endl;
      cout<<"Height"<<height<<"cm"<<endl;
      cout<<"Volume"<<volume<<"cm^3"<<endl;
    }
    //add accessor a.k.a get functions
    int getWidth()
    {
      return width;
    }
    int getLength()
    {
      return length;
    }
    int getHeight()
    {
      return height;
    }
    int getVolume()
    {
      return volume;
    }
};//class closing braces

void Cuboid::findVolume()//calculate the cube volume
{
  volume = width * length * height;	
}

int main()
{ 
  Cuboid Q;
  Q.setdata();
  Q.findVolume();
  //Q.display();
  cout<<"\n-------------Display Cuboid Data--------------"<<endl;
  //calling the accessor functions to display data members of object
  cout<<"Width"<<Q.getWidth()<<"cm"<<endl;
  cout<<"Length"<<Q.getLength()<<"cm"<<endl;
  cout<<"Height"<<Q.getHeight()<<"cm"<<endl;
  cout<<"Volume"<<Q.getVolume()<<"cm^3"<<endl;
  return 0;
}