#include <iostream>
#include <iomanip>

using namespace std;

class Box
{
private:
    /* data */
public:
    float length,width,height;
    float volume()
    {
        return length*width*height;
    }
};


int main() 
{
    Box box1;
    box1.length = 5;
    box1.width = 6;
    box1.height = 7;

    Box box2;
    box2.length = 10;
    box2.width = 12;
    box2.height = 13;

    cout << "Volume of Box 1: " << box1.volume() << endl;
    cout << "Volume of Box 2: " << box2.volume() << endl;
}