#include <iostream>
 
using namespace std;
 
class Cuboid {
public:
  int length, width, height, volume;
 
  void setdata() {
    cout << "Enter the width, length, height of a Cuboid object :";
    cin >> width >> length >> height;
  }
 
  void findVolume() {
    volume = length * width * height;
  }
 
  void display() {
    cout << "------Display Cuboid Data-----\n";
    cout << "Width :" << width << " cm\n";
    cout << "Length :" << length << " cm\n";
    cout << "Height :" << height << " cm\n";
    cout << "Volume :" << volume << " cm^3\n";
  }
};
 
int main() {
  Cuboid Q;
  Q.setdata();
  Q.findVolume();
  Q.display();
  return 0;
}