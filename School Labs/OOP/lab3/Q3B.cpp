#include <iostream>
#include <string.h>
using namespace std;
 
class Purchase
{
   private:
    char name[30], code[10];
    int qty;
    float price, total;
   public:
    //function prototypes
    void set_data(char[],char[],int, float);
    void calculate();
    void print();
};
void Purchase::set_data(char n[],char c[],int q, float p)
{
    strcpy(name,n);//copy input string character-by-character
    strcpy(code,c);
    qty=q;
    price=p;
}
void Purchase::calculate()
{
    total=qty * price;
}
void Purchase::print()
{
    cout<<"============================="<<endl;
    cout<<"           RECEIPT           "<<endl;
    cout<<"============================="<<endl;
    cout<<"Name:"<<name<<endl;
    cout<<"Product Code:"<<code<<endl;
    cout<<"Quantity:"<<qty<<endl;
    cout<<"Product Price:"<<price<<endl;
    cout<<"Total Payment:"<<total<<endl;
}
int main()
{
    char nama[30], kod[10], ans;
    int ktt;
    float harga;
    Purchase p;
    do
    {
        cout<<"========================="<<endl;
        cout<<"         WELCOME         "<<endl;
        cout<<"========================="<<endl;
        cout<<"Enter name: ";
        cin>>nama;
        cout<<"Product code: ";
        cin>>kod;
        cout<<"Enter quantity: ";
        cin>>ktt;
        cout<<"Enter price: ";
        cin>>harga;
        p.set_data(nama, kod, ktt, harga);
        p.calculate();
        p.print();
        cout<<"Do you have another customer to purchase item? [Y/N]:";
        cin>>ans;
    }while(ans=='Y'||ans!='N');
}