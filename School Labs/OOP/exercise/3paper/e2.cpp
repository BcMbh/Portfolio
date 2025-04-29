#include <iostream>
using namespace std;

class Furniture
{
   private:
      int order;
      float cost;
      
   public:
      float price();
      void setCost (float c) { cost = c; }
      void setOrder(int o)   { order = o; }
      void setOrder() { order = 3; }
      float getOrder() { return order; }
}; 

float Furniture::price()
{
    return cost * order;
}


int main()
{
    Furniture Cavenzi;

    Cavenzi.setCost(42.5);
    Cavenzi.setOrder(7);

    cout << "The total cost is: RM " << Cavenzi.price() << endl;

    return 0;
}
