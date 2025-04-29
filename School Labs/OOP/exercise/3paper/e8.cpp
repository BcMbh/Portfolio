#include<iostream>
using namespace std;

class Test
{
    private:
    int x,y;

    public:
    Test(){
        x=0,y=0;
    }
    Test(int a,int b){
        x=a,y=b;
    }

    Test operator+(Test t){
        return Test(x+t.x, y+t.y);
    }

    Test operator-(Test t){
        return Test(x-t.x, y-t.y);
    }

    void display(){
        cout<<"x = "<<x<<endl;
        cout<<"y = "<<y<<endl;
    }
};

int main() 
{
    Test p1(4.0, 10.0);
    Test p2(6.0, 3.0);
    Test p3;
    p1.display();
    p2.display();

    p3 = p1 - p2 ; 
    p3.display();
    p3 = p1 + p2; 
    p3.display();
}	
