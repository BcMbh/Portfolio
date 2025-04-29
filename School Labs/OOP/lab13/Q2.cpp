#include <iostream>
using namespace std;
 
class Produce{
    private:
        float price, total;
        int qty;
    public:
        Produce()//default constructor
        {
            price=0.0;
            total=0.0;
            qty=0.0;
        }
        void set_input(float p, int q)
        {
            price=p;
            qty=q;
            total=price*qty;
            cout<<"Sub total:RM "<<total<<endl;
        }
        friend class Bill;
};
class Bill{
    private: 
        float grand_total;
    public:
        Bill()//default constructor
        {
            grand_total=0.0;
        }
        void display()
        {
            cout<<"The grand total of the bill is RM: "<<grand_total<<endl;
        }
        void operator+=(const Produce &P)
        {
            //accumulate subtotals from Produce items into grand total
            grand_total=grand_total+P.total;
        }
};
 
int main() {
    Bill bl;
    Produce pd;
    float pr;
    int quan;
    char answer;
    do{
        cout<<"Eneter price: ";
        cin>>pr;
        cout<<"Enter quantity: ";
        cin>>quan;
        pd.set_input(pr, quan);
        bl+=pd;

        cout<<"Do you wnat to ccontinue?";
        cin>>answer;

    }while (answer=='y'|| answer=='Y');

    bl.display();
}